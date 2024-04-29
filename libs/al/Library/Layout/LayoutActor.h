#pragma once

#include <prim/seadSafeString.h>
#include <al/Library/Audio/IUseAudioKeeper.h>
#include <al/Library/Camera/IUseCamera.h>
#include <al/Library/Effect/IUseEffectKeeper.h>
#include <al/Library/Execute/LayoutExecuteInfo.h>
#include <al/Library/HostIO/IUseHioNode.h>
#include <al/Library/Layout/IUseLayout.h>
#include <al/Library/Layout/IUseLayoutAction.h>
#include <al/Library/Message/IUseMessageSystem.h>
#include <al/Library/Nerve/IUseNerve.h>
#include <al/Library/Camera/CameraDirector.h>
#include <al/Library/Scene/SceneObjHolder.h>

namespace al {
    class NerveKeeper;

    class LayoutKeeper;

    class LayoutActionKeeper;

    class LayoutTextPaneAnimator;

    class EffectKeeper;

    class AudioKeeper;

    class HitReactionKeeper;

    class LayoutSceneInfo;

    class LayoutPartsActorKeeper;

    class MessageSystem;

    class Nerve;

    class LayoutActor : public al::IUseHioNode,
                        public al::IUseNerve,
                        public al::IUseLayout,
                        public al::IUseLayoutAction,
                        public al::IUseMessageSystem,
                        public al::IUseCamera,
                        public al::IUseAudioKeeper,
                        public al::IUseEffectKeeper,
                        public al::IUseSceneObjHolder {
    private:
        sead::FixedSafeString<0x80> mName;
        al::NerveKeeper *mNerveKeeper;
        al::LayoutKeeper *mLayoutKeeper;
        al::LayoutActionKeeper *mLayoutActionKeeper;
        al::LayoutTextPaneAnimator *mTextPaneAnimator;
        al::EffectKeeper *mEffectKeeper;
        al::AudioKeeper *mAudioKeeper;
        al::LayoutExecuteInfo *mExecuteInfo;
        al::HitReactionKeeper *mHitReactionKeeper;
        al::LayoutSceneInfo *mLayoutSceneInfo;
        al::LayoutPartsActorKeeper *mLayoutPartsActorKeeper;
        bool mIsAlive;

    public:
        LayoutActor(char const *);

        virtual void appear();

        virtual void kill();

        virtual void control() {}

        virtual void calcAnim(bool recursive);

        virtual void movement();

        virtual al::NerveKeeper *getNerveKeeper() const override;

        virtual const char *getName() const override;

        virtual al::EffectKeeper *getEffectKeeper() const override;

        virtual al::AudioKeeper *getAudioKeeper() const override;

        virtual al::LayoutActionKeeper *getLayoutActionKeeper() const override;

        virtual al::LayoutKeeper *getLayoutKeeper() const override;

        virtual al::CameraDirector *getCameraDirector() const override;

        virtual al::SceneObjHolder *getSceneObjHolder() const override;

        virtual const al::MessageSystem *getMessageSystem() const override;

        void initLayoutKeeper(al::LayoutKeeper *);

        void initActionKeeper(void);

        void initTextPaneAnimator(al::LayoutTextPaneAnimator *);

        void initExecuteInfo(al::LayoutExecuteInfo *);

        void initHitReactionKeeper(al::HitReactionKeeper *);

        void initSceneInfo(al::LayoutSceneInfo *);

        void initLayoutPartsActorKeeper(s32);

        void initEffectKeeper(al::EffectKeeper *);

        void initAudioKeeper(al::AudioKeeper *);

        void initNerve(const al::Nerve *, s32);

        void setMainGroupName(const char *);

        void syncAction();

        al::LayoutExecuteInfo *getExecuteInfo() { return mExecuteInfo; }
    };
}  // namespace al