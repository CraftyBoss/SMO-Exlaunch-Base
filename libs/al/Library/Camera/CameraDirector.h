#pragma once

#include "CameraTicket.h"
#include "../Player/PlayerHolder.h"
#include "../Placement/PlacementId.h"
#include "../../../sead/math/seadMatrix.h"
#include "../HostIO/HioNode.h"
#include "../Execute/IUseExecutor.h"
#include "CameraResourceHolder.h"

namespace al {

    class NameToCameraParamTransferFunc;

    class AreaObjDirector;

    class SceneCameraInfo;

    class SceneCameraCtrl;

    class CameraPoseUpdater;

    class CameraPoserFactory;

    class CameraPoserSceneInfo;

    class CameraTicketHolder;

    class SpecialCameraHolder;

    class CameraTargetCollideInfoHolder;

    class CameraTargetHolder;

    class CameraInputHolder;

    class CameraAngleVerticalRequester;

    class CameraStartParamCtrl;

    class CameraStopJudge;

    class CameraParamTransfer;

    class CameraFlagCtrl;

    class CameraInSwitchOnAreaDirector;

    class CameraRailHolder;

    class ICameraInput;

    class IUseAudioKeeper;

    class CameraDirector : public al::HioNode, public al::IUseExecutor {
    private:
        int mMaxCameras;
        int unkInt1;
        SceneCameraInfo *mCameraInfo;
        SceneCameraCtrl *mCameraCtrl;
        CameraPoseUpdater **mUpdaterList;
        CameraPoserFactory *mFactory;
        CameraPoserSceneInfo *mSceneInfo;
        CameraTicketHolder *mTicketHolder;
        SpecialCameraHolder *mSpecialHolder;
        CameraTargetCollideInfoHolder *mCollideInfoHolder;
        CameraTargetHolder *mTargetHolder;
        CameraInputHolder *mInputHolder;
        CameraAngleVerticalRequester *mAngleVerticalRequester;
        CameraStartParamCtrl *mStartParamCtrl;
        CameraStopJudge *mStopJudge;
        CameraParamTransfer *mParamTransfer;
        CameraResourceHolder *mResourceHolder;
        CameraFlagCtrl *mFlagCtrl;
        void *unkArrayStruct;
        CameraInSwitchOnAreaDirector *mInSwitchOnAreaDirector;
        void *unkPtr;
    public:
        void init(al::CameraPoserSceneInfo *, al::CameraPoserFactory const *);

        al::CameraPoseUpdater *getPoseUpdater(int) const;

        void endInit(al::PlayerHolder const *);

        al::CameraTicket *
        createCameraFromFactory(char const *creatorName, al::PlacementId const *, char const *, int priority,
                                sead::Matrix34f const &);

        void createCamera(al::CameraPoser *, al::PlacementId const *, char const *, int, sead::Matrix34f const &, bool);

        void execute(void) override;

        void update(void);

        void createObjectCamera(al::PlacementId const *, char const *, char const *, int, sead::Matrix34f const &);

        void createObjectEntranceCamera(al::PlacementId const *, char const *, sead::Matrix34f const &);

        void createMirrorObjectCamera(al::PlacementId const *, char const *, int, sead::Matrix34f const &);

        void initAreaCameraSwitcherMultiForPrototype(al::AreaObjDirector *);

        al::ICameraInput *getCameraInput(int);

        void setCameraInput(al::ICameraInput const *);

        void setViewCameraInput(al::ICameraInput const *, int);

        void initAreaCameraSwitcherSingle(void);

        void initResourceHolder(al::CameraResourceHolder const *);

        void registerCameraRailHolder(al::CameraRailHolder *);

        void initSceneFovyDegree(float);

        void setCameraParamTransferFuncTable(al::NameToCameraParamTransferFunc const *, int);

        void initSettingCloudSea(float);

        void initSnapShotCameraAudioKeeper(al::IUseAudioKeeper *);

        void initAndCreatePauseCameraCtrl(float);

        float getSceneFovyDegree(void) const;

        void validateCameraArea2D(void);

        void invalidateCameraArea2D(void);

        void stopByDeathPlayer(void);

        void restartByDeathPlayer(void);

        void startInvalidStopJudgeByDemo(void);

        void endInvalidStopJudgeByDemo(void);

        void startSnapShotMode(bool);

        void endSnapShotMode(void);
    };
}