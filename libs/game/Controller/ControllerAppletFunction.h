#pragma once

#include <al/Library/Controller/GamePadSystem.h>

class ControllerAppletFunction {
    public:
        void connectControllerSinglePlay(al::GamePadSystem *);
        void connectControllerSeparatePlay(al::GamePadSystem *);
};