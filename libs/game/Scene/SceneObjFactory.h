#pragma once

#include <al/Library/Scene/SceneObjHolder.h>
#include <types.h>

class SceneObjFactory {
public:
    static al::SceneObjHolder* createSceneObjHolder();
};

al::ISceneObj* createObj(s32);