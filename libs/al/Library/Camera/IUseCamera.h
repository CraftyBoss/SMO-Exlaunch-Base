#pragma once

#include <al/Library/Camera/CameraDirector.h>

namespace al {

    class IUseCamera {
    public:
        virtual CameraDirector *getCameraDirector() const = 0;
    };
}  // namespace al
