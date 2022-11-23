#include "lib.hpp"
#include "imgui_backend/imgui_impl_nvn.hpp"
#include "patches.hpp"
#include "nn/err.h"
#include "nvn/nvn_CppFuncPtrImpl.h"
#include "logger/Logger.hpp"
#include "fs.h"

#include <basis/seadRawPrint.h>
#include <prim/seadSafeString.h>
#include <resource/seadResourceMgr.h>
#include <filedevice/nin/seadNinSDFileDeviceNin.h>
#include <filedevice/seadFileDeviceMgr.h>
#include <filedevice/seadPath.h>
#include <resource/seadArchiveRes.h>
#include <framework/seadFramework.h>
#include <heap/seadHeapMgr.h>
#include <heap/seadExpHeap.h>
#include <devenv/seadDebugFontMgrNvn.h>
#include <gfx/seadTextWriter.h>
#include <gfx/seadViewport.h>

#include "rs/util.hpp"

#include "game/StageScene/StageScene.h"
#include "game/System/GameSystem.h"
#include "game/System/Application.h"
#include "game/HakoniwaSequence/HakoniwaSequence.h"

#include "al/util.hpp"
#include "al/fs/FileLoader.h"

#include "agl/detail/ShaderHolder.h"

static const char *DBG_FONT_PATH   = "DebugData/Font/nvn_font_jis1.ntx";
static const char *DBG_SHADER_PATH = "DebugData/Font/nvn_font_shader_jis1.bin";
static const char *DBG_TBL_PATH    = "DebugData/Font/nvn_font_jis1_tbl.bin";

sead::TextWriter *gTextWriter;

nvn::Device* nvnDevice;
nvn::Queue* nvnQueue;
nvn::CommandBuffer* nvnCmdBuf;

void graNoclipCode(al::LiveActor *player) {

    static bool isFirst = true;

    float speed = 25.0f;
    float speedMax = 150.0f;
    float vspeed = 20.0f;
    float speedGain = 0.0f;

    sead::Vector3f *playerPos = al::getTransPtr(player);
    sead::Vector3f *cameraPos = al::getCameraPos(player, 0);
    sead::Vector2f *leftStick = al::getLeftStick(-1);

    // Its better to do this here because loading zones reset this.
    al::offCollide(player);
    al::setVelocityZero(player);

    // Mario slightly goes down even when velocity is 0. This is a hacky fix for that.
    playerPos->y += 1.4553f;

    float d = sqrt(al::powerIn(playerPos->x - cameraPos->x, 2) + (al::powerIn(playerPos->z - cameraPos->z, 2)));
    float vx = ((speed + speedGain)/d)*(playerPos->x - cameraPos->x);
    float vz = ((speed + speedGain)/d)*(playerPos->z - cameraPos->z);

    if (!al::isPadHoldZR(-1)) {
        playerPos->x -= leftStick->x * vz;
        playerPos->z += leftStick->x * vx;

        playerPos->x += leftStick->y * vx;
        playerPos->z += leftStick->y * vz;

        if (al::isPadHoldX(-1)) speedGain -= 0.5f;
        if (al::isPadHoldY(-1)) speedGain += 0.5f;
        if (speedGain <= 0.0f) speedGain = 0.0f;
        if (speedGain >= speedMax) speedGain = speedMax;

        if (al::isPadHoldZL(-1) || al::isPadHoldA(-1)) playerPos->y -= (vspeed + speedGain/6);
        if (al::isPadHoldB(-1)) playerPos->y += (vspeed + speedGain/6);
    }
}

void controlLol(StageScene* scene) {
    auto actor = rs::getPlayerActor(scene);

    static bool isNoclip = false;

    if(al::isPadTriggerRight(-1)) {
        isNoclip = !isNoclip;

        if(!isNoclip) {
            al::onCollide(actor);
        }
    }

    if(isNoclip) {
        graNoclipCode(actor);
    }
}

constexpr int getShaderIndex(const char *shaderName) {
    for (size_t i = 0; i < ACNT(agl::detail::programs); i++)
    {
        if(al::isEqualString(shaderName, agl::detail::programs[i].mProgramName)) {
            return i;
        }
    }
}

NOINLINE void* getFragmentShaderFromAgl(const char *shaderName) {

    agl::ShaderProgram *shader = agl::detail::ShaderHolder::instance()->mShaders(getShaderIndex(shaderName));

    if(shader) {
        return shader->mFragmentShader.mShaderBinary;
    }

    return nullptr;
}

NOINLINE void *getVertexShaderFromAgl(const char *shaderName) {
    agl::ShaderProgram *shader = agl::detail::ShaderHolder::instance()->mShaders(getShaderIndex(shaderName));

    if(shader) {
        return shader->mVertexShader.mShaderBinary;
    }

    return nullptr;
}

HOOK_DEFINE_TRAMPOLINE(ControlHook) {
    static void Callback(StageScene* scene) {
        controlLol(scene);
        Orig(scene);
    }
};

HOOK_DEFINE_REPLACE(ReplaceSeadPrint) {
    static void Callback(const char* format, ...) {
        va_list args;
        va_start(args, format);
        Logger::log(format, args);
        va_end(args);
    }
};

HOOK_DEFINE_TRAMPOLINE(CreateFileDeviceMgr) {
    static void Callback(sead::FileDeviceMgr *thisPtr) {
        
        Orig(thisPtr);

        thisPtr->mMountedSd = nn::fs::MountSdCardForDebug("sd").isSuccess();

        sead::NinSDFileDevice *sdFileDevice = new sead::NinSDFileDevice();

        thisPtr->mount(sdFileDevice);
    }
};

HOOK_DEFINE_TRAMPOLINE(RedirectFileDevice) {
    static sead::FileDevice *Callback(sead::FileDeviceMgr *thisPtr, sead::SafeString &path, sead::BufferedSafeString *pathNoDrive) {

        sead::FixedSafeString<32> driveName;
        sead::FileDevice* device;

        // Logger::log("Path: %s\n", path.cstr());

        if (!sead::Path::getDriveName(&driveName, path))
        {
            
            device = thisPtr->findDevice("sd");

            if(!(device && device->isExistFile(path))) {

                device = thisPtr->getDefaultFileDevice();

                if (!device)
                {
                    Logger::log("drive name not found and default file device is null\n");
                    return nullptr;
                }

            }else {
                Logger::log("Found File on SD! Path: %s\n", path.cstr());
            }
            
        }
        else
            device = thisPtr->findDevice(driveName);

        if (!device)
            return nullptr;

        if (pathNoDrive != NULL)
            sead::Path::getPathExceptDrive(pathNoDrive, path);

        return device;
    }
};

HOOK_DEFINE_TRAMPOLINE(FileLoaderLoadArc) {
    static sead::ArchiveRes *Callback(al::FileLoader *thisPtr, sead::SafeString &path, const char *ext, sead::FileDevice *device) {

        // Logger::log("Path: %s\n", path.cstr());

        sead::FileDevice* sdFileDevice = sead::FileDeviceMgr::instance()->findDevice("sd");

        if(sdFileDevice && sdFileDevice->isExistFile(path)) {

            Logger::log("Found File on SD! Path: %s\n", path.cstr());

            device = sdFileDevice;
        }

        return Orig(thisPtr, path, ext, device);
    }
};

HOOK_DEFINE_TRAMPOLINE(FileLoaderIsExistFile) {
    static bool Callback(al::FileLoader *thisPtr, sead::SafeString &path, sead::FileDevice *device) {

        sead::FileDevice* sdFileDevice = sead::FileDeviceMgr::instance()->findDevice("sd");

        if(sdFileDevice && sdFileDevice->isExistFile(path)) device = sdFileDevice;

        return Orig(thisPtr, path, device);
    }
};

HOOK_DEFINE_TRAMPOLINE(GameSystemInit) {
    static void Callback(GameSystem *thisPtr) {

        sead::Heap* curHeap = sead::HeapMgr::instance()->getCurrentHeap();

        sead::DebugFontMgrJis1Nvn::createInstance(curHeap);

        if (al::isExistFile(DBG_SHADER_PATH) && al::isExistFile(DBG_FONT_PATH) && al::isExistFile(DBG_TBL_PATH)) {
            sead::DebugFontMgrJis1Nvn::sInstance->initialize(curHeap, DBG_SHADER_PATH, DBG_FONT_PATH, DBG_TBL_PATH, 0x100000);
        }

        sead::TextWriter::setDefaultFont(sead::DebugFontMgrJis1Nvn::sInstance);

        al::GameDrawInfo* drawInfo = Application::instance()->mDrawInfo;

        agl::DrawContext *context = drawInfo->mDrawContext;
        agl::RenderBuffer* renderBuffer = drawInfo->mFirstRenderBuffer;

        sead::Viewport* viewport = new sead::Viewport(*renderBuffer);

        gTextWriter = new sead::TextWriter(context, viewport);

        gTextWriter->setupGraphics(context);

        gTextWriter->mColor = sead::Color4f(1.f, 1.f, 1.f, 0.8f);

        if(nvnDevice && nvnQueue) {

            Logger::log("Creating ImGui.\n");

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;

            void *vertShader = getVertexShaderFromAgl("draw_imm");
            void *fragShader = getFragmentShaderFromAgl("draw_imm");

            if(vertShader && fragShader) {
                Logger::log("Accessed Vertex and Fragment Shaders for draw_imm!\n");
            }

            ImGui::StyleColorsDark();

            ImguiNvnBackend::InitBackend(nvnDevice, nvnQueue, nvnCmdBuf);

        }else {
            Logger::log("Unable to create ImGui Renderer!\n");
        }

        Orig(thisPtr);

    }
};

HOOK_DEFINE_TRAMPOLINE(DrawDebugMenu) {
    static void Callback(HakoniwaSequence *thisPtr) { 

        Orig(thisPtr);
        
        gTextWriter->beginDraw();

        gTextWriter->setCursorFromTopLeft(sead::Vector2f(10.f, 10.f));
        gTextWriter->printf("FPS: %d\n", static_cast<int>(round(Application::instance()->mFramework->calcFps())));

        gTextWriter->endDraw();
    }
};

nvn::DeviceInitializeFunc tempDeviceInitFuncPtr;
nvn::DeviceGetProcAddressFunc tempGetProcAddressFuncPtr;
nvn::QueueInitializeFunc tempQueueInitFuncPtr;
nvn::CommandBufferInitializeFunc tempBufferInitFuncPtr;

NVNboolean deviceInit(nvn::Device *device, const nvn::DeviceBuilder *builder) {
    NVNboolean result = tempDeviceInitFuncPtr(device, builder);
    nvnDevice = device;
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
        Logger::log("Overrriding Proc: %s\n", procName);
        tempQueueInitFuncPtr = (nvn::QueueInitializeFunc)ptr;
        return (nvn::GenericFuncPtrFunc)&queueInit;
    }else if(strcmp(procName, "nvnCommandBufferInitialize") == 0) {
        Logger::log("Overrriding Proc: %s\n", procName);
        tempBufferInitFuncPtr = (nvn::CommandBufferInitializeFunc)ptr;
        return (nvn::GenericFuncPtrFunc)&cmdBufInit;
    } else if (device != nullptr) {
        Logger::log("Getting Proc: %s\n", procName);
    }

    return ptr;
}

HOOK_DEFINE_TRAMPOLINE(NvnBootstrapHook) {
    static void *Callback(const char *funcName) {

        void *result = Orig(funcName);

        Logger::log("Getting Nvn Func: %s\n", funcName);

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

extern "C" void exl_main(void* x0, void* x1) {
    /* Setup hooking enviroment. */
    envSetOwnProcessHandle(exl::util::proc_handle::Get());
    exl::hook::Initialize();

    R_ABORT_UNLESS(Logger::instance().init(LOGGER_IP, 3080).value);

    runCodePatches();

    GameSystemInit::InstallAtOffset(0x535850);

    // SD File Redirection

    RedirectFileDevice::InstallAtOffset(0x76CFE0);
    FileLoaderLoadArc::InstallAtOffset(0xA5EF64);
    CreateFileDeviceMgr::InstallAtOffset(0x76C8D4);
    FileLoaderIsExistFile::InstallAtOffset(0xA5ED28);

    // Sead Debugging Overriding

    ReplaceSeadPrint::InstallAtOffset(0xB59E28);

    // Debug Text Writer Drawing

    DrawDebugMenu::InstallAtOffset(0x50F1D8);

    ControlHook::InstallAtSymbol("_ZN10StageScene7controlEv");

    // ImGui Hooks

    NvnBootstrapHook::InstallAtSymbol("nvnBootstrapLoader");
}

extern "C" NORETURN void exl_exception_entry() {
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}