#pragma once

#include <al/Library/Audio/AudioKeeper.h>
#include <al/Library/Audio/AudioDirector.h>
#include <al/Library/Audio/IUseAudioKeeper.h>
#include <al/Library/Nerve/NerveExecutor.h>
#include <al/Library/Scene/SceneCreator.h>
#include <al/Library/System/GameSystemInfo.h>

#include <prim/seadSafeString.h>

namespace al {

    struct SequenceInitInfo {
        al::GameSystemInfo* mGsysInfo;
    };

    class AudioSystemInfo;

    class Scene;

    class DrawSystemInfo;

    class Sequence : public al::NerveExecutor, public al::IUseAudioKeeper, public al::IUseSceneCreator {
    public:
        Sequence(const char *name);

        virtual ~Sequence() override;

        virtual void init(const al::SequenceInitInfo &initInfo);

        virtual void update();

        virtual void kill();

        virtual void drawMain() const;

        virtual void drawSub() const;

        virtual bool isDisposable() { return false; }

        virtual al::Scene *getCurrentScene() const;

        virtual al::SceneCreator *getSceneCreator() const override;

        virtual void setSceneCreator(al::SceneCreator *sceneCreator) override;

        virtual al::AudioKeeper *getAudioKeeper() const override;

        void initAudio(const al::GameSystemInfo &, const char *, int, int, int, const char *);

        void initAudioKeeper(const char *);

        void initDrawSystemInfo(const al::SequenceInitInfo &);

        al::AudioSystemInfo *getAudioSystemInfo();

        al::DrawSystemInfo *getDrawSystemInfo() const {
            return mGameDrawInfo;
        }

        al::AudioDirector *getAudioDirector() const {
            return mAudioDirector;
        }

        void setNextScene(al::Scene *scene) {
            mNextScene = scene;
        }

        const sead::SafeString &getName() const {
            return mName;
        }
    private:
        const sead::FixedSafeString<0x40> mName;
        al::Scene *mNextScene;
        al::Scene *mCurrentScene;
        al::SceneCreator *mSceneCreator;
        al::AudioDirector *mAudioDirector;
        al::AudioKeeper *mAudioKeeper;
        al::DrawSystemInfo *mGameDrawInfo;
        bool mIsAlive;
    };
}