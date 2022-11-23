#include "imgui_impl_nvn.hpp"
#include "lib.hpp"

namespace ImguiNvnBackend {

NvnBackendData* getBackendData() {
    NvnBackendData *result = ImGui::GetCurrentContext() ? (NvnBackendData*)ImGui::GetIO().BackendRendererUserData : nullptr;
    EXL_ASSERT(result, "Backend has not been initialized!");
    return result;
}

void setupShaders(void* vertShaderBinary, ulong vertShaderSize, void* fragShaderBinary, ulong fragShaderSize) {
    auto bd = getBackendData();

    int codeMemSize = vertShaderSize + fragShaderSize;

    bd->shaderProgram.Initialize(bd->device);

    bd->memPoolBuilder.SetDefaults();
    bd->memPoolBuilder.SetDevice(bd->device);
    bd->memPoolBuilder.SetFlags(nvn::MemoryPoolFlags::CPU_UNCACHED | nvn::MemoryPoolFlags::GPU_CACHED |
                           nvn::MemoryPoolFlags::SHADER_CODE);

    bd->memPoolBuilder.SetStorage(vertShaderBinary, codeMemSize);

    bd->bufferPool.Initialize(&bd->memPoolBuilder);

    bd->bufferBuilder.SetDefaults();
    bd->bufferBuilder.SetDevice(bd->device);

    int codeMemOffset = 0;
    bd->bufferBuilder.SetStorage(&bd->bufferPool, codeMemOffset, vertShaderSize); // storage for vert shader
    bd->vertShaderBuffer.Initialize(&bd->bufferBuilder);

    nvn::ShaderData shaderData;
    shaderData.data = bd->vertShaderBuffer.GetAddress();
    shaderData.control = vertShaderBinary;
}

void InitBackend(nvn::Device* device, nvn::Queue *queue, nvn::CommandBuffer *cmdBuf) {
    ImGuiIO &io = ImGui::GetIO();
    EXL_ASSERT(!io.BackendRendererUserData, "Already Initialized Imgui Backend!");

    io.BackendPlatformName = "Switch";
    io.BackendRendererName = "imgui_impl_nvn";
    io.IniFilename = nullptr;
    io.MouseDrawCursor = false;
    io.ConfigFlags |= ImGuiConfigFlags_IsTouchScreen;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.BackendFlags |= ImGuiBackendFlags_HasGamepad;
    io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;

    auto *bd = new NvnBackendData();
    io.BackendRendererUserData = (void*)bd;

    bd->device = device;
    bd->queue = queue;
    bd->cmdBuf = cmdBuf;
}

void ShutdownBackend() {}

void newFrame() {}

void renderDrawData(ImDrawData* drawData) {

    auto bd = getBackendData();

    bd->queue->Flush();

    // if(drawData->Valid) {
    //     for (size_t i = 0; i < drawData->CmdListsCount; i++)
    //     {
    //         auto cmdList = drawData->CmdLists[i];

    //         for(auto cmd : cmdList->CmdBuffer) {

    //         }

    //     }
    // }

}

}
