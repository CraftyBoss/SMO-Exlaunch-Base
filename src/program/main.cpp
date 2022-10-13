#include "lib.hpp"
#include "patches.hpp"
#include "nn/err.h"
#include "logger/Logger.hpp"
#include "fs.hpp"

#include <basis/seadRawPrint.h>
#include <prim/seadSafeString.h>
#include <resource/seadResource.h>
#include <resource/seadArchiveRes.h>

#include "game/StageScene/StageScene.h"
#include "rs/util.hpp"
#include "al/util.hpp"

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
        Logger::log("logus\n");
        svcBreak(0x1234, 0x5678, 0x9);

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

HOOK_DEFINE_TRAMPOLINE(ReplaceSeadPrint) {
    static void Callback(const char* format, ...) {
        va_list args;
        va_start(args, format);
        Logger::log(format, args);
        va_end(args);
    }
};

HOOK_DEFINE_TRAMPOLINE(CrashOnTitle) {
    static void Callback() {
        svcBreak(0x12,0,0);
    }
};

HOOK_DEFINE_TRAMPOLINE(OpenFile) {
    static sead::ArchiveRes* Callback(sead::SafeString const &path, char const *extension, sead::FileDevice *fileDevice) {
        
        Logger::log("Opening File With Ext %s At Path: %s\n", extension, path.cstr());
        
        return Orig(path, extension, fileDevice);
    }
};

extern "C" void exl_main(void* x0, void* x1) {
    /* Setup hooking enviroment. */
    envSetOwnProcessHandle(exl::util::proc_handle::Get());
    exl::hook::Initialize();

    // R_ABORT_UNLESS(Logger::instance().init("64.201.219.20", 3080).value);
    R_ABORT_UNLESS(Logger::instance().init("10.0.0.224", 3080).value);

    nn::fs::MountSdCardForDebug("sd");

    // DisableUserExceptionHandler::InstallAtFuncPtr(nn::os::SetUserExceptionHandler);

    ReplaceSeadPrint::InstallAtOffset(0xB59E28);

    ControlHook::InstallAtSymbol("_ZN10StageScene7controlEv");

    OpenFile::InstallAtOffset(0xA5EF64);

    runCodePatches();

}

extern "C" NORETURN void exl_exception_entry() {
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}