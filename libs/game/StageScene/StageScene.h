#pragma once

#include <al/Library/Scene/Scene.h>
#include <game/Layouts/MapLayout.h>

#include "game/GameData/GameDataHolderAccessor.h"
#include "game/StageScene/StageSceneLayout.h"
#include "game/StageScene/StageSceneStatePauseMenu.h"

namespace al {
    class LayoutTextureRenderer;
    class SimpleAudioUser;
    class ParabolicPath;
    class DemoSyncedEventKeeper;
    class ChromakeyDrawer;
    class WipeHolder;
}

class StageSceneStateWorldMap;
class StageSceneStateShop;
class StageSceneStateSnapShot;
class StageSceneStateGetShine;
class StageSceneStateGetShineMain;
class StageSceneStateGetShineGrand;
class StageSceneStateCollectBgm;
class StageSceneStateCollectionList;
class StageSceneStateMiniGameRanking;
class StageSceneStateCloset;
class StageSceneStateSkipDemo;
class StageSceneStateCheckpointWarp;
class StageSceneStateCarryMeat;

class StageSceneStateMiss;
class StageSceneStateYukimaruRace;
class StageSceneStateYukimaruRaceTutorial;
class StageSceneStateRaceManRace;
class StageSceneStateRadicon;
class StageSceneStateScenarioCamera;
class StageSceneStateRecoverLife;
class StageSceneStateGetShineMainSandWorld;
class StageSceneStateWarp;
class ScenarioStartCameraHolder;
class PlayGuideSkip;
class CinemaCaption;
class ControllerGuideSnapShotCtrl;

class MiniGameMenu;
class TimeBalloonNpc;
class ProjectItemDirector;
class Pyramid;
class DemoSoundSynchronizer;
class ProjectSeNamedList;
class TimeBalloonDirector;
class TimeBalloonSequenceInfo;
class CollectBgmPlayer;
class CollectBgmRegister;
class BgmAnimeSyncDirector;
class NpcEventDirector;

class ProjectNfpDirector;

class StageScene : public al::Scene {
public:
    bool isPause() const;

    sead::FixedSafeString<0x40> mStageName;
    int field_130;
    StageSceneStateWorldMap *mStateWorldMap;
    StageSceneStateShop *mStateShop;
    StageSceneStateSnapShot *mStateSnapShot;
    StageSceneStateGetShine *mStateGetShine;
    StageSceneStateGetShineMain *mStateGetShineMain;
    StageSceneStateGetShineGrand *mStateGetShineGrand;
    StageSceneStateCollectBgm *mStateCollectBgm;
    StageSceneStateCollectionList *mStateCollectionList;
    StageSceneStateMiniGameRanking *mStateMiniGameRanking;
    StageSceneStatePauseMenu *mStatePauseMenu;
    StageSceneStateCloset *mStateCloset;
    StageSceneStateSkipDemo *mStateSkipDemo;
    StageSceneStateCheckpointWarp *mStateCheckpointWarp;
    StageSceneStateCarryMeat *mStateCarryMeat;
    void *field_1A8;
    void *field_1B0;
    StageSceneStateMiss *mStateMiss;
    StageSceneStateYukimaruRace *mStateYukimaruRace;
    StageSceneStateYukimaruRaceTutorial *mStateYukimaruRaceTutorial;
    StageSceneStateRaceManRace *mStateRaceManRace;
    StageSceneStateRadicon *mStateRadicon;
    StageSceneStateScenarioCamera *mStateScenarioCamera;
    StageSceneStateRecoverLife *mStateRecoverLife;
    StageSceneStateGetShineMainSandWorld *mStateGetShineMainSandWorld;
    void *field_1F8;
    StageSceneStateWarp *field_200;
    void *field_208;
    ScenarioStartCameraHolder *field_210;
    sead::FixedSafeString<0x40> field_218;
    sead::FixedSafeString<0x40> field_270;
    void *qword2C8;
    GameDataHolderAccessor mHolder;
    void *qword2D8;
    al::LayoutTextureRenderer *qword2E0;
    PlayGuideSkip *mPlayGuideSkip;
    CinemaCaption *mCinemaCaption;
    StageSceneLayout *mSceneLayout;
    char field_300;
    char field_301;
    al::SimpleLayoutAppearWaitEnd *char308;
    al::SimpleLayoutAppearWaitEnd *field_310;
    al::SimpleLayoutAppearWaitEnd *field_318;
    ControllerGuideSnapShotCtrl *mCtrlGuideSnapCtrl;
    InputSeparator *field_328;
    al::WipeSimple *field_330;
    al::WipeHolder *field_338;
    void *field_340;
    al::WindowConfirm *field_348;
    MiniGameMenu *field_350;
    bool field_358;
    char gap359[15];
    char char368;
    MapLayout *field_370;
    al::SimpleLayoutAppearWaitEnd *field_378;
    al::LiveActorGroup *field_380;
    void *field_388;
    void *mKoopaLv1Actor;
    TimeBalloonNpc *mTimeBalloonNpc;
    ProjectItemDirector *field_3A0;
    Pyramid *field_3A8;
    void *field_3B0;
    al::Nerve *field_3B8;
    SceneAudioSystemPauseController *field_3C0;
    DemoSoundSynchronizer *mDemoSoundSynchronizer;
    al::SimpleAudioUser *mStageStartAtmosSe;
    al::SimpleAudioUser *mSePlayArea;
    al::SimpleAudioUser *mSnapShotCameraCtrlAudio;
    ProjectSeNamedList *field_3E8;
    void *field_3F0;
    TimeBalloonDirector *mTimeBalloonDirector;
    TimeBalloonSequenceInfo *mTimeBalloonSequenceInfo;
    void *qword408;
    void *qword410;
    sead::Vector3f qword418;
    sead::Vector3f qword424;
    void *qword430;
    int dword438;
    const al::LiveActor *field_440;
    al::ParabolicPath *field_448;
    al::LiveActor *field_450;
    void *qword458;
    int dword460;
    CollectBgmPlayer *qword468;
    CollectBgmRegister *qword470;
    BgmAnimeSyncDirector *qword478;
    al::DemoSyncedEventKeeper *field_480;
    void *field_488;
    int field_490;
    NpcEventDirector *qword498;
    al::ChromakeyDrawer *field_4A0;
    void *qword4A8;
    ProjectNfpDirector *qword4B0;
    void *qword4B8;
};
