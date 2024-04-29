#pragma once

#include <al/Library/Nerve/NerveExecutor.h>
#include <al/Library/Audio/IUseAudioKeeper.h>
#include <al/Library/Stage/IUseStageSwitch.h>
#include <al/Library/Camera/IUseCamera.h>
#include <al/Library/LiveActor/LiveActor.h>

struct AppearSwitchTimer : al::NerveExecutor {
    void *qword10;
    void *qword18;
    void *qword20;
    void *qword28;
    void *qword30;
    void *qword38;
    void *qword40;
    void *qword48;
    int dword50;
    void *qword58;
    int dword60;
    int dword64;
    int mValidFrame;
    short word6C;
    bool byte6E;

    AppearSwitchTimer(void);

    ~AppearSwitchTimer();

    void init(al::ActorInitInfo const &, al::IUseAudioKeeper const *, al::IUseStageSwitch *, al::IUseCamera *,
              al::LiveActor *);

    void onSwitch(void);

    void isSwitchOn(void);

    void offSwitch(void);

    void isDemoPlaying(void);

    void exeWaitAppearDemoStart(void);

    void exeWaitAppearDemoCameraInterpoling(void);

    void exeAppearDemo(void);

    void procAppearDitherAnim(int);

    void exeOnWait(void);

    void getLastFrame(void);

    void exeOnWaitBlink(void);

    void exeOffWait(void);

};