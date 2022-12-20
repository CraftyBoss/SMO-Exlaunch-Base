#include "imgui_nvn.h"
#include "imgui_backend/imgui_impl_nvn.hpp"
#include "init.h"
#include "lib.hpp"
#include "logger/Logger.hpp"

nvn::Device* nvnDevice;
nvn::Queue* nvnQueue;
nvn::CommandBuffer* nvnCmdBuf;
nvn::TexturePool *nvnTexPool;
nvn::SamplerPool *nvnSamplerPool;

nvn::DeviceGetProcAddressFunc tempGetProcAddressFuncPtr;
nvn::CommandBufferInitializeFunc tempBufferInitFuncPtr;

nvn::DeviceInitializeFunc tempDeviceInitFuncPtr;
nvn::QueueInitializeFunc tempQueueInitFuncPtr;
nvn::TexturePoolInitializeFunc tempTexPoolInitFuncPtr;
nvn::SamplerPoolInitializeFunc tempSamplerPoolInitFuncPtr;

NVNboolean deviceInit(nvn::Device *device, const nvn::DeviceBuilder *builder) {
    NVNboolean result = tempDeviceInitFuncPtr(device, builder);
    nvnDevice = device;
    return result;
}

NVNboolean texturePoolInit(nvn::TexturePool *texPool, const nvn::MemoryPool *memPool, ptrdiff_t offset, int numDescriptors) {
    NVNboolean result = tempTexPoolInitFuncPtr(texPool, memPool, offset, numDescriptors);
    EXL_ASSERT(!nvnTexPool, "Texture Pool has already been initialized!");
    nvnTexPool = texPool;
    return result;
}

NVNboolean samplerPoolInit(nvn::SamplerPool *sampPool, const nvn::MemoryPool *memPool, ptrdiff_t offset, int numDescriptors) {
    NVNboolean result = tempSamplerPoolInitFuncPtr(sampPool, memPool, offset, numDescriptors);
    EXL_ASSERT(!nvnSamplerPool, "Sampler Pool has already been initialized!");
    nvnSamplerPool = sampPool;
    return result;
}

NVNboolean queueInit(nvn::Queue *queue, const nvn::QueueBuilder *builder) {
    NVNboolean result = tempQueueInitFuncPtr(queue, builder);
    nvnQueue = queue;
    return result;
}

NVNboolean cmdBufInit(nvn::CommandBuffer *buffer, nvn::Device *device) {
    NVNboolean result = tempBufferInitFuncPtr(buffer, device);
    nvnCmdBuf = buffer;
    return result;
}

nvn::GenericFuncPtrFunc getProc(nvn::Device *device, const char *procName) {

    nvn::GenericFuncPtrFunc ptr = tempGetProcAddressFuncPtr(nvnDevice, procName);

    if(strcmp(procName, "nvnQueueInitialize") == 0) {
        tempQueueInitFuncPtr = (nvn::QueueInitializeFunc)ptr;
        return (nvn::GenericFuncPtrFunc)&queueInit;
    }else if(strcmp(procName, "nvnCommandBufferInitialize") == 0) {
        tempBufferInitFuncPtr = (nvn::CommandBufferInitializeFunc)ptr;
        return (nvn::GenericFuncPtrFunc)&cmdBufInit;
    }else if(strcmp(procName, "nvnTexturePoolInitialize") == 0) {
        tempTexPoolInitFuncPtr = (nvn::TexturePoolInitializeFunc)ptr;
        return (nvn::GenericFuncPtrFunc)&texturePoolInit;
    }else if(strcmp(procName, "nvnSamplerPoolInitialize") == 0) {
        tempSamplerPoolInitFuncPtr = (nvn::SamplerPoolInitializeFunc)ptr;
        return (nvn::GenericFuncPtrFunc)&samplerPoolInit;
    }

    return ptr;
}

HOOK_DEFINE_TRAMPOLINE(NvnBootstrapHook) {
    static void *Callback(const char *funcName) {

        void *result = Orig(funcName);

        if(strcmp(funcName, "nvnDeviceInitialize") == 0) {
            tempDeviceInitFuncPtr = (nvn::DeviceInitializeFunc)result;
            return (void*)&deviceInit;
        }if(strcmp(funcName, "nvnDeviceGetProcAddress") == 0) {
            tempGetProcAddressFuncPtr = (nvn::DeviceGetProcAddressFunc)result;
            return (void*)&getProc;
        }

        return result;
    }
};

// TODO: move this hook into a game agnostic location
HOOK_DEFINE_TRAMPOLINE(ImGuiRenderFrameHook) {
    static void* Callback(void *thisPtr) {
        void *result = Orig(thisPtr);

        ImguiNvnBackend::newFrame();
        ImGui::NewFrame();

        bool isOpen = true;
        ImGui::ShowDemoWindow(&isOpen);

        ImGui::Render();
        ImguiNvnBackend::renderDrawData(ImGui::GetDrawData());

        return result;
    }
};

void nvnImGui::InstallHooks() {
    NvnBootstrapHook::InstallAtSymbol("nvnBootstrapLoader");
    ImGuiRenderFrameHook::InstallAtSymbol("_ZN2al15GameFrameworkNx9procDraw_Ev");
}

bool nvnImGui::InitImGui() {
    if(nvnDevice && nvnQueue) {

        Logger::log("Creating ImGui.\n");

        IMGUI_CHECKVERSION();

        ImGuiMemAllocFunc allocFunc = [](size_t size, void* user_data) {
            return nn::init::GetAllocator()->Allocate(size);
        };

        ImGuiMemFreeFunc freeFunc = [](void* ptr, void* user_data) {
            nn::init::GetAllocator()->Free(ptr);
        };

        ImGui::SetAllocatorFunctions(allocFunc, freeFunc, nullptr);

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsDark();

        nvn::nvnLoadCPPProcs(nvnDevice, tempGetProcAddressFuncPtr);

        ImguiNvnBackend::NvnBackendInitInfo initInfo = {
            .device = nvnDevice,
            .queue = nvnQueue,
            .cmdBuf = nvnCmdBuf,
            .texPool = nvnTexPool,
            .samplerPool = nvnSamplerPool
        };

        ImguiNvnBackend::InitBackend(initInfo);

        return true;

    }else {
        Logger::log("Unable to create ImGui Renderer!\n");

        return false;
    }
}