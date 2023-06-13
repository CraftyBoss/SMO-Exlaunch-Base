#pragma once

#include "PlayerAnimFrameCtrl.h"
#include "PlayerModelHolder.h"
#include "sead/prim/seadSafeString.hpp"

namespace al {
    class ActorDitherAnimator;
}

class PlayerAnimator {
    public:
        PlayerAnimator(PlayerModelHolder const*,al::ActorDitherAnimator *);

        void startAnim(const sead::SafeString &animName);
        void startSubAnim(const sead::SafeString &animName);
        void startSubAnimOnlyAir(const sead::SafeString &animName);
        void startUpperBodyAnimAndHeadVisKeep(const sead::SafeString &animName);
        void startAnimDead(void); // chooses one of the 5 death animations and starts that animation
        void endSubAnim(void);

        void updateAnimFrame(void);
        void updateModel(void);
        void updateModelAlpha(void);
        void updateEyeControlAnim(void);
        void clearUpperBodyAnim(void);

        bool isAnimEnd(void) const;
        bool isAnim(const sead::SafeString &animName) const;
        bool isCurrentAnimOneTime(void) const;
        bool isSubAnimEnd(void) const;
        bool isSubAnim(sead::SafeString const &subAnimName) const;
        bool isUpperBodyAnimAttached(void) const;
        bool isUpperBodyAnimEnd(void) const;
        bool isUpperBodyAnim(sead::SafeString const &upperBodyAnim) const;

        float getAnimFrame(void) const;
        float getAnimFrameMax(void) const;
        float getAnimFrameRate(void) const;
        float getSubAnimFrame(void) const;
        float getSubAnimFrameMax(void) const;
        float getBlendWeight(int index);
        float getModelAlpha(void) const;
        float getMario3DWaitFrameMax(void) const;
        float getRunStartAnimFrameMax(void) const;
        float getRunStartAnimBlendRate(void) const;

        void setAnimRate(float);
        void setAnimRateCommon(float);
        void setAnimFrame(float);
        void setAnimFrameCommon(float);
        void setSubAnimFrame(float);
        void setSubAnimRate(float);
        void setBlendWeight(float,float,float,float,float,float);
        void setModelAlpha(float);
        void setPartsAnimRate(float, char const*);
        void setPartsAnimFrame(float, char const*);

        void copyAnim(void);
        void startAnimCommon(sead::SafeStringBase<char> const&);
        void startAnimSpinAttack(sead::SafeStringBase<char> const&);
        void clearInterpolation(void);
        void applyBlendWeight(void);
        void startUpperBodyAnim(sead::SafeStringBase<char> const&);
        void startPartsPartialAnim(sead::SafeStringBase<char> const&);
        void startUpperBodyAnimSubParts(sead::SafeStringBase<char> const&);
        void startPress(void);
        void forceCapOn(void);
        void forceCapOff(void);
        void resetModelAlpha(void);
        void endDemoInvalidateModelAlpha(void);
        void startSnapShotMode(void);
        void endSnapShotMode(void);
        void startEyeControlAnim(bool);
        void endEyeControlAnim(int);
        void clearEndEyeControlAnimDelay(void);
        void startRightHandAnim(char const*);
        void overwrideYoshiEatVis(void);
        void restartYoshiActionVis(void);
        void recordRunStartAnimRate(float);
        void calcModelJointRootMtx(sead::Matrix34<float> *);
        void startPartsAnim(sead::SafeStringBase<char> const&);
        void copyAnimLocal(void);

        PlayerModelHolder *mModelHolder; // 0x0
        al::LiveActor *mPlayerDeco; // 0x8
        al::LiveActor *mCurrentModelActor; // 0x10
        PlayerAnimFrameCtrl *mAnimFrameCtrl; // 0x18
        sead::FixedSafeString<0x40> curAnim;
        sead::FixedSafeString<0x40> curSubAnim;
        sead::FixedSafeString<0x40> unkStr1;
        sead::FixedSafeString<0x40> unkStr2;
        al::ActorDitherAnimator *mActorDitherAnimator;
        float *mBlendWeights;
        float mEyeStartMtsAnimFrame;
        int mLookAtEyeKeepFrame;
        float mRunStartAnimBlendRate;
        int mModelAlpha;
        bool mIsNeedFaceAnim;
        bool mIsSetBlendWeights;
        bool mIsActiveSubAnim;
        bool mIsNeedClearSkl;
        bool mIsUpperBodyAnimKeepHeadVis;
        bool mIsEyeControlAnim;
        bool mUnkEyeControlBool;
        bool mIsSubAnimOnlyAir;
};

static_assert(sizeof(PlayerAnimator) == 0x1A8, "PlayerAnimator Size");