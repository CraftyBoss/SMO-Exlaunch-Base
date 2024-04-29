#pragma once

#include <al/Library/Resource/Resource.h>
#include <al/Library/Yaml/ByamlIter.h>
#include <al/Library/Placement/PlacementId.h>
#include "CameraTicket.h"

namespace al {
    class CameraResourceHolder {
    private:
    public:
        CameraResourceHolder(char const *, int);

        bool tryInitCameraResource(al::Resource const *, int);

        bool tryFindParamResource(al::ByamlIter *, al::CameraTicketId const *, int) const;

        bool tryFindCameraParamList(al::ByamlIter *, al::PlacementId const *, char const *);

        void calcEntranceCameraParamNum(void);

        void tryFindCameraParamList(al::ByamlIter *, char const *, char const *);

        void getEntranceCameraParamResource(al::ByamlIter *, int);

        void findCameraResource(char const *);

        void tryFindCameraResource(char const *);

        void tryFindCameraResource(al::PlacementId const *);
    };
}