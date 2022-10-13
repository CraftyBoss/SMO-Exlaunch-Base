#include "lib.hpp"
#include "patches.hpp"
#include "nn/err.h"
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

#include "game/StageScene/StageScene.h"
#include "game/System/GameSystem.h"
#include "rs/util.hpp"

#include "al/util.hpp"
#include "al/fs/FileLoader.h"

static const char *DBG_FONT_PATH   = "DebugData/Font/nvn_font_jis1.ntx";
static const char *DBG_SHADER_PATH = "DebugData/Font/nvn_font_shader_jis1.bin";
static const char *DBG_TBL_PATH    = "DebugData/Font/nvn_font_jis1_tbl.bin";

sead::TextWriter *gTextWriter;

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

HOOK_DEFINE_TRAMPOLINE(ControlHook) {
    static void Callback(StageScene* scene) {
        controlLol(scene);
        Orig(scene);   
    }
};

HOOK_DEFINE_TRAMPOLINE(DisableUserExceptionHandler) {
    static void Callback(void (*)(nn::os::UserExceptionInfo*), void*, u64, nn::os::UserExceptionInfo*) {
        Logger::log("this is so cool\n");

        static char ALIGNED(0x1000) exceptionStack[0x6000];
        static nn::os::UserExceptionInfo exceptionInfo;
        Orig([](nn::os::UserExceptionInfo* exceptionInfo){
            Logger::log("Among us!!!!!! %p\n", exceptionInfo->PC.x);
            for (size_t i = 0; i < 29; i++)
            {
                Logger::log("my nuts! %p\n", exceptionInfo->CpuRegisters[i].x);
            }
        }, exceptionStack, sizeof(exceptionStack), &exceptionInfo);

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

        Logger::log("Path: %s\n", path.cstr());

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
                Logger::log("Found Replacement File on SD! Path: %s\n", path.cstr());
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

        Logger::log("Path: %s\n", path.cstr());

        sead::FileDevice* sdFileDevice = sead::FileDeviceMgr::instance()->findDevice("sd");

        if(sdFileDevice && sdFileDevice->isExistFile(path)) {

            Logger::log("Found Replacement File on SD! Path: %s\n", path.cstr());

            device = sdFileDevice;
        }

        return Orig(thisPtr, path, ext, device);
    }
}
;

extern "C" void exl_main(void* x0, void* x1) {
    /* Setup hooking enviroment. */
    envSetOwnProcessHandle(exl::util::proc_handle::Get());
    exl::hook::Initialize();

    runCodePatches();

    // R_ABORT_UNLESS(Logger::instance().init("64.201.219.20", 3080).value);
    R_ABORT_UNLESS(Logger::instance().init("10.0.0.224", 3080).value);

    // SD File Redirection

    RedirectFileDevice::InstallAtOffset(0x76CFE0);
    FileLoaderLoadArc::InstallAtOffset(0xA5EF64);
    CreateFileDeviceMgr::InstallAtOffset(0x76C8D4);

    // Sead Debugging Overriding

    ReplaceSeadPrint::InstallAtOffset(0xB59E28);

    ControlHook::InstallAtSymbol("_ZN10StageScene7controlEv");


}

extern "C" NORETURN void exl_exception_entry() {
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}