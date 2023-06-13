#pragma once

#include <al/Library/Audio/IUseAudioKeeper.h>
#include <al/Library/Nerve/NerveExecutor.h>
#include <al/Library/Scene/SceneInitInfo.h>
#include <al/Library/Scene/SceneObjHolder.h>
#include <al/Library/LiveActor/ActorInitInfo.h>
#include <al/Library/Camera/IUseCamera.h>

namespace al {

    class StageResourceKeeper;
    class LiveActorKit;
    class LayoutKit;

    class SceneStopCtrl;
    class SceneMsgCtrl;
    class ScreenCoverCtrl;
    class AudioDirector;

    class GraphicsInitArg;

class Scene : public al::NerveExecutor,
              public al::IUseAudioKeeper,
              public al::IUseCamera,
              public al::IUseSceneObjHolder {
private:
    bool mIsAlive;

    sead::FixedSafeString<0x40> mName;
    StageResourceKeeper *mStageResourceKeeper;
    LiveActorKit *mLiveActorKit;
    LayoutKit *mLayoutKit;
    SceneObjHolder *mSceneObjHolder;
    SceneStopCtrl *mSceneStopCtrl;
    SceneMsgCtrl *mSceneMsgCtrl;
    ScreenCoverCtrl *mScreenCoverCtrl;
    AudioDirector *mAudioDirector;
    AudioKeeper *mAudioKeeper;
    NerveKeeper *mNerveKeeper;

    void initLiveActorKitImpl(const al::SceneInitInfo &, int, int, int);

public:
    Scene(const char *name);
    virtual ~Scene();

    virtual void init(const al::SceneInitInfo &);
    virtual void appear();
    virtual void kill();
    virtual void movement();
    virtual void control();
    virtual void drawMain();
    virtual void drawSub();

    AudioKeeper* getAudioKeeper() const override;
    SceneObjHolder* getSceneObjHolder() const override;
    CameraDirector* getCameraDirector() const override;
    LayoutKit* getLayoutKit() const;
    SceneStopCtrl* getSceneStopCtrl() const;
    SceneMsgCtrl* getSceneMsgCtrl() const;
    void initializeAsync(const al::SceneInitInfo &);
    void initDrawSystemInfo(const al::SceneInitInfo &);
    void initSceneObjHolder(al::SceneObjHolder *);
    void initAndLoadStageResource(const char *, int);
    void initLiveActorKit(const al::SceneInitInfo &, int, int, int);
    void initLiveActorKitWithGraphics(const al::GraphicsInitArg &, const al::SceneInitInfo &, int, int, int);
    void initLayoutKit(const al::SceneInitInfo &);
    void initSceneStopCtrl();
    void initSceneMsgCtrl();
    void initScreenCoverCtrl();
    void endInit(const al::ActorInitInfo &);

};
}
