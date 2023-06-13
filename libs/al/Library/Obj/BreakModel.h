#pragma once

#include <al/Library/LiveActor/LiveActor.h>

namespace al {
class BreakModel : public LiveActor {
private:
    const LiveActor *mParent;
    const sead::Matrix34f *mRootMtx;
    const char *mModelName;
    const char *mBreakAction;
    const char *mInitSuffix;
    f32 mActionFrameRate = 1.0f;
    bool mIsValid = false;
    s32 mStep = 0;
public:
    BreakModel(const LiveActor* rootActor, char const* objName, char const* modelName,
               char const* fileSuffixName, const sead::Matrix34f* rootMtx, char const* breakActionName);
    void init(ActorInitInfo const&);
    void appear();
    void exeWait();
    void exeBreak();
};
static_assert(sizeof(BreakModel) == 0x140, "al::BreakModel Size");
}