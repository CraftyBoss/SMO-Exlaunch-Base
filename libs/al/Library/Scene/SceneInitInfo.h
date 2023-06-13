#pragma once

#include <al/Library/System/GameDataHolderBase.h>
#include <al/Library/System/GameSystemInfo.h>
#include <al/Library/Audio/AudioDirector.h>

#include <prim/seadSafeString.h>

namespace al {

    class ScreenCaptureExecutor;

    struct SceneInitInfo {
        const al::GameSystemInfo *mSystemInfo;
        al::GameDataHolderBase *mDataHolderBase;
        al::ScreenCaptureExecutor *mScreenCaptureExectuor;
        const char *mStageName;
        int mScenarioNo;
        sead::FixedSafeString<0x200> mSequenceTypeName; // "Sequence=ProductSequence"
        al::AudioDirector *mAudioDirector;
    };
}