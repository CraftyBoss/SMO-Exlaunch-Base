#pragma once

#include <gfx/seadCamera.h>
#include "IUseCamera.h"
#include "CameraTicket.h"

namespace al {
    class IUseCamera;

    class SceneCameraInfo;

    sead::LookAtCamera *getLookAtCamera(al::IUseCamera const *, int);

    sead::Vector3f *getCameraUp(al::IUseCamera const *, int);

    sead::Vector3f *getCameraPos(al::IUseCamera const *, int);

    sead::Projection *getProjectionSead(al::IUseCamera const *, int);

//    al::Projection *getProjection(al::IUseCamera const *, int);

    void setCameraInterpoleStep(al::CameraTicket *, int);

    bool isActiveCameraInterpole(al::IUseCamera const *, int);

    bool isActiveCameraInterpole(al::SceneCameraInfo const *, int);

    void startCameraInterpole(al::IUseCamera const *, int, int);

    void requestCancelCameraInterpole(al::IUseCamera const *, int);
} // namespace al