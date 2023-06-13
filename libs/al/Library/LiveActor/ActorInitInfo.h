#pragma once

#include <al/Library/LiveActor/ActorFactory.h>
#include <al/Library/LiveActor/ActorSceneInfo.h>
#include <al/Library/Nerve/NerveUtil.h>
#include <al/Library/Resource/Resource.h>
#include <al/Library/Scene/SceneObjHolder.h>
#include <al/Library/Yaml/ByamlIter.h>
#include <basis/seadTypes.h>
#include <gfx/seadColor.h>
#include <gfx/seadDrawContext.h>
#include <math/seadBoundBox.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>

namespace al {
class LiveActor;
class LiveActorGroup;
class PlacementInfo;
class LayoutInitInfo;
class AreaObjDirector;
class CameraDirector;
class ClippingDirector;
class CollisionDirector;
class DemoDirector;
class GameDataHolderBase;
class GravityHolder;
class ItemDirectorBase;
class NatureDirector;
class GamePadSystem;
class PadRumbleDirector;
class PlayerHolder;
class SceneStopCtrl;
class SceneMsgCtrl;
class ScreenCoverCtrl;
class ShadowDirector;
class ModelGroup;
class GraphicsSystemInfo;
class ModelDrawBufferCounter;
class ActorResourceHolder;
class ActorResource;
class AudioDirector;
class EffectSystemInfo;
class ExecuteDirector;
class HitSensorDirector;
class StageSwitchDirector;
class ScreenPointDirector;
class ViewIdHolder;
class SceneCameraInfo;
class Nerve;
class PlacementInfo;
class LayoutInitInfo;
class AudioDirector;
class CollisionDirector;
class GraphicsSystemInfo;

class ActorInitInfo {
private:
    al::LiveActorGroup* mKitDrawingGroup;
    const al::PlacementInfo* mPlacementInfo;
    const al::LayoutInitInfo* mLayoutInitInfo;
    al::ActorSceneInfo mActorSceneInfo;
    al::LiveActorGroup* mAllActorsGroup;
    const al::ActorFactory* mActorFactory;
    al::ActorResourceHolder* mActorResourceHolder;
    al::AudioDirector* mAudioDirector;
    al::EffectSystemInfo* mEffectSystemInfo;
    al::ExecuteDirector* mExecuteDirector;
    al::HitSensorDirector* mHitSensorDirector;
    al::ScreenPointDirector* mScreenPointDirector;
    al::StageSwitchDirector* mStageSwitchDirector;
    al::ViewIdHolder* mViewIdHolder;

public:
    ActorInitInfo();
    void initNew(const PlacementInfo*, const LayoutInitInfo*, LiveActorGroup*, const ActorFactory*, ActorResourceHolder*, AreaObjDirector*,
                 AudioDirector*, CameraDirector*, ClippingDirector*, CollisionDirector*, DemoDirector*, EffectSystemInfo*, ExecuteDirector*,
                 GameDataHolderBase*, GravityHolder*, HitSensorDirector*, ItemDirectorBase*, NatureDirector*, const GamePadSystem*,
                 PadRumbleDirector*, PlayerHolder*, SceneObjHolder*, SceneMsgCtrl*, SceneStopCtrl*, ScreenCoverCtrl*, ScreenPointDirector*,
                 ShadowDirector*, StageSwitchDirector*, ModelGroup*, GraphicsSystemInfo*, ModelDrawBufferCounter*, LiveActorGroup*);
    void initViewIdSelf(const PlacementInfo*, const ActorInitInfo&);
    void copyHostInfo(const ActorInitInfo&, const PlacementInfo*);
    void initViewIdHost(const PlacementInfo*, const ActorInitInfo&);
    void initViewIdHostActor(const ActorInitInfo&, const LiveActor*);
    void initNoViewId(const PlacementInfo*, const ActorInitInfo&);

    const al::PlacementInfo& getPlacementInfo() const { return *mPlacementInfo; }
};

void initActor(al::LiveActor* actor, const al::ActorInitInfo& initInfo);
void initActorSuffix(al::LiveActor* actor, const al::ActorInitInfo& initInfo, const char* suffix);
void initActorWithArchiveName(al::LiveActor* actor, const al::ActorInitInfo& initInfo, const sead::SafeString& archiveName, const char* suffix);
void initChildActorWithArchiveNameWithPlacementInfo(al::LiveActor* actor, const al::ActorInitInfo& initInfo, const sead::SafeString& archiveName,
                                                    const char* suffix);
void initChildActorWithArchiveNameNoPlacementInfo(al::LiveActor* actor, const al::ActorInitInfo& initInfo, const sead::SafeString& archiveName,
                                                  const char* suffix);
void initMapPartsActor(al::LiveActor* actor, const al::ActorInitInfo& initInfo, const char* suffix);
void initLinksActor(al::LiveActor* actor, const al::ActorInitInfo& initInfo, const char* suffix, s32 linkIndex);

// TODO: move these
void initActorSceneInfo(al::LiveActor *,const al::ActorInitInfo&);
void initExecutorUpdate(al::LiveActor *,al::ActorInitInfo const&,const char *);
void initExecutorDraw(al::LiveActor *,al::ActorInitInfo const&,const char *);
void initExecutorPlayer(al::LiveActor *,const al::ActorInitInfo&);
void initExecutorPlayerPreMovement(al::LiveActor *,const al::ActorInitInfo&);
void initExecutorPlayerMovement(al::LiveActor *,const al::ActorInitInfo&);
void initExecutorPlayerModel(al::LiveActor *,const al::ActorInitInfo&);
void initExecutorPlayerDecoration(al::LiveActor *,const al::ActorInitInfo&);
void initExecutorEnemy(al::LiveActor *,const al::ActorInitInfo&);
void initExecutorEnemyMovement(al::LiveActor *,const al::ActorInitInfo&);
void initExecutorEnemyDecoration(al::LiveActor *,const al::ActorInitInfo&);
void initExecutorEnemyDecorationMovement(al::LiveActor *,const al::ActorInitInfo&);
void initExecutorMapObj(al::LiveActor *,const al::ActorInitInfo&);
void initExecutorMapObjMovement(al::LiveActor *,const al::ActorInitInfo&);
void initExecutorMapObjDecoration(al::LiveActor *,const al::ActorInitInfo&);
void initExecutorNpcDecoration(al::LiveActor *,const al::ActorInitInfo&);
void initExecutorShadowVolume(al::LiveActor *,const al::ActorInitInfo&);
void initExecutorShadowVolumeFillStencil(al::LiveActor *,const al::ActorInitInfo&);
void initExecutorCollisionMapObjDecorationMovement(al::LiveActor *,const al::ActorInitInfo&);
void initExecutorWatchObj(al::LiveActor *,const al::ActorInitInfo&);
void initExecutorDebugMovement(al::LiveActor *,const al::ActorInitInfo&);
void initExecutorModelUpdate(al::LiveActor *,const al::ActorInitInfo&);
void initExecutorDrcAssistMovement(al::LiveActor *,const al::ActorInitInfo&);

void initActorPoseTRSV(al::LiveActor *);
void initActorPoseTRMSV(al::LiveActor *);
void initActorPoseTRGMSV(al::LiveActor *);
void initActorPoseTFSV(al::LiveActor *);
void initActorPoseTFUSV(al::LiveActor *);
void initActorPoseTFGSV(al::LiveActor *);
void initActorPoseTQSV(al::LiveActor *);
void initActorPoseTQGSV(al::LiveActor *);
void initActorPoseTQGMSV(al::LiveActor *);

void initActorSRT(al::LiveActor *, const al::ActorInitInfo &);

void initActorModelKeeper(al::LiveActor *,al::ActorInitInfo const&,al::ActorResource const*,int);
void initActorModelKeeper(al::LiveActor *,al::ActorInitInfo const&,char const*,int,char const*);
void initActorModelKeeperByHost(al::LiveActor *,al::LiveActor const*);
void initActorModelForceCubeMap(al::LiveActor *,al::ActorInitInfo const&);
void initActorActionKeeper(al::LiveActor *,al::ActorInitInfo const&,char const*,char const*);
void initActorActionKeeper(al::LiveActor *,al::ActorResource const*,char const*,char const*);
void initActorEffectKeeper(al::LiveActor *,al::ActorInitInfo const&,char const*);
void initActorSeKeeper(al::LiveActor *,al::ActorInitInfo const&,char const*,sead::Vector3<float> const*,sead::Matrix34f const*);
void initActorSeKeeper(al::LiveActor *,al::ActorInitInfo const&,char const*);
void initActorSeKeeperWithout3D(al::LiveActor *,al::ActorInitInfo const&,char const*);
void initActorBgmKeeper(al::LiveActor *,al::ActorInitInfo const&,char const*);
void isInitializedBgmKeeper(al::LiveActor *);
void initHitReactionKeeper(al::LiveActor *,char const*);
void initHitReactionKeeper(al::LiveActor *,al::Resource const*,char const*);
void initActorParamHolder(al::LiveActor *,char const*);
void initActorParamHolder(al::LiveActor *,al::Resource const*,char const*);
void initDepthShadowMapCtrl(al::LiveActor *,al::Resource const*,al::ActorInitInfo const&,char const*);
void initDepthShadowMapCtrlWithoutIter(al::LiveActor *,int,bool);
void addDepthShadowMapInfo(al::LiveActor const*,char const*,int,int,int,float,bool,sead::Vector3<float> const&,bool,sead::Vector3<float> const&,sead::Vector3<float> const&,bool,char const*,int,bool,float,float,float,bool,bool,float,int,bool);
void declareUseDepthShadowMap(al::LiveActor const*,int);
void createDepthShadowMap(al::LiveActor const*,char const*,int,int,int);
void initShadowMaskCtrl(al::LiveActor *,al::ActorInitInfo const&,al::ByamlIter const&,char const*);
void initShadowMaskCtrlWithoutInitFile(al::LiveActor *,al::ActorInitInfo const&,int);

void createShadowMaskSphere(al::LiveActor *,char const*,char const*,char const*);
void createShadowMaskCube(al::LiveActor *,char const*,char const*,char const*,sead::Color4f const&,sead::Vector3<float> const&,float,float,float,sead::Vector3<float> const&,float);
void createShadowMaskCylinder(al::LiveActor *,char const*,char const*,char const*,sead::Color4f const&,sead::Vector3<float> const&,float,float,float,float,float);
void createShadowMaskCastOvalCylinder(al::LiveActor *,char const*,char const*,char const*,sead::Color4f const&,sead::Vector3<float> const&,sead::Vector3<float> const&,float,float,float,float);
//void initActorCollision(al::LiveActor *,sead::SafeStringBase<char> const&,al::HitSensor *,sead::Matrix34<float> const*);
//void initActorCollisionWithResource(al::LiveActor *,al::Resource const*,sead::SafeStringBase<char> const&,al::HitSensor *,sead::Matrix34<float> const*,char const*);
//void initActorCollisionWithArchiveName(al::LiveActor *,sead::SafeStringBase<char> const&,sead::SafeStringBase<char> const&,al::HitSensor *,sead::Matrix34<float> const*);
//void initActorCollisionWithFilePtr(al::LiveActor *,void *,void const*,al::HitSensor *,sead::Matrix34<float> const*,char const*,char const*,int);
void initStageSwitch(al::LiveActor *,al::ActorInitInfo const&);
void initActorItemKeeper(al::LiveActor *,al::ActorInitInfo const&,al::ByamlIter const&);
void initActorPrePassLightKeeper(al::LiveActor *,al::Resource const*,al::ActorInitInfo const&,char const*);
void initActorOcclusionKeeper(al::LiveActor *,al::Resource const*,al::ActorInitInfo const&,char const*);
void initSubActorKeeper(al::LiveActor *,al::ActorInitInfo const&,char const*,int);
void initSubActorKeeperNoFile(al::LiveActor *,al::ActorInitInfo const&,int);
void registerSubActor(al::LiveActor *,al::LiveActor *);
void registerSubActorSyncClipping(al::LiveActor *,al::LiveActor *);
void registerSubActorSyncClippingAndHide(al::LiveActor *,al::LiveActor *);
void registerSubActorSyncAll(al::LiveActor *,al::LiveActor *);
void setSubActorOffSyncClipping(al::LiveActor *);
void initScreenPointKeeper(al::LiveActor *,al::Resource const*,al::ActorInitInfo const&,char const*);
void initScreenPointKeeperNoYaml(al::LiveActor *,int);
void initActorMaterialCategory(al::LiveActor *,al::ActorInitInfo const&,char const*);

void createChildLinkSimpleActor(const char* actorName, const char* archiveName, const al::ActorInitInfo& initInfo, bool alive);
void createChildLinkMapPartsActor(const char* actorName, const char* archiveName, const al::ActorInitInfo& initInfo, s32 linkIndex, bool alive);

al::ActorInitInfo* createLinksPlayerActorInfo(al::LiveActor* actor, const al::ActorInitInfo& initInfo);

void initCreateActorWithPlacementInfo(al::LiveActor *,al::ActorInitInfo const&);
void initCreateActorWithPlacementInfo(al::LiveActor *,al::ActorInitInfo const&,al::PlacementInfo const&);
void initCreateActorNoPlacementInfo(al::LiveActor *,al::ActorInitInfo const&);
void initCreateActorNoPlacementInfoNoViewId(al::LiveActor *, const al::ActorInitInfo&);
void createPlacementActorFromFactory(const al::ActorInitInfo&, const al::PlacementInfo*);
void createLinksActorFromFactory(const al::ActorInitInfo&,char const*,int);
void createLinksActorGroupFromFactory(const al::ActorInitInfo&,char const*,char const*);
void tryCreateLinksActorGroupFromFactory(const al::ActorInitInfo&,char const*,char const*);
void tryCreateLinksActorFromFactorySingle(const al::ActorInitInfo&,char const*);
void createAndRegisterLinksActorFromFactory(al::LiveActorGroup *,al::ActorInitInfo const&,char const*);
void makeMapPartsModelName(sead::BufferedSafeString *,sead::BufferedSafeString *,const al::PlacementInfo&);
void makeMapPartsModelName(sead::BufferedSafeString *,sead::BufferedSafeString *,const al::ActorInitInfo&);

void initNerve(al::LiveActor* actor, const al::Nerve* nerve, s32 maxStates);
void initNerveAction(al::LiveActor* actor, const char* actionName, alNerveFunction::NerveActionCollector* collector, s32 maxStates);

bool trySyncStageSwitchAppear(al::LiveActor* actor);
bool trySyncStageSwitchKill(al::LiveActor* actor);
bool trySyncStageSwitchAppearAndKill(al::LiveActor* actor);
bool tryListenStageSwitchAppear(al::LiveActor* actor);
bool tryListenStageSwitchKill(al::LiveActor* actor);

void syncSensorScaleY(al::LiveActor* actor);
void syncSensorAndColliderScaleY(al::LiveActor* actor);

void setMaterialCode(al::LiveActor* actor, const char*);
void initMaterialCode(al::LiveActor* actor, const al::ActorInitInfo& initInfo);

bool tryAddDisplayRotate(al::LiveActor* actor, const al::ActorInitInfo& initInfo);
bool tryAddDisplayOffset(al::LiveActor* actor, const al::ActorInitInfo& initInfo);
bool tryAddDisplayScale(al::LiveActor* actor, const al::ActorInitInfo& initInfo);

al::PlacementInfo* getPlacementInfo(const al::ActorInitInfo& initInfo);
const al::LayoutInitInfo* getLayoutInitInfo(const al::ActorInitInfo& initInfo);
al::AudioDirector* getAudioDirector(const al::ActorInitInfo& initInfo);
al::CollisionDirector* getCollisionDirectorFromInfo(const al::ActorInitInfo& initInfo);
const al::SceneCameraInfo* getSceneCameraInfoFromInfo(const al::ActorInitInfo& initInfo);
al::GraphicsSystemInfo* getGraphicsSystemInfo(const al::ActorInitInfo& initInfo);
sead::DrawContext* getDrawContext(const al::ActorInitInfo& initInfo);

void getActorRecourseDataF32(f32*, al::LiveActor*, const char*, const char*);
void getActorRecourseDataString(const char**, al::LiveActor*, const char*, const char*);
void getActorRecourseDataV3f(sead::Vector3f*, al::LiveActor* actor, const char*, const char*);
void getActorRecourseDataBox3f(sead::BoundBox3f* box, al::LiveActor* actor, const char*, const char*);

void createPartsEffectGroup(al::LiveActor* actor, const al::ActorInitInfo& initInfo, s32);
}  // namespace al
