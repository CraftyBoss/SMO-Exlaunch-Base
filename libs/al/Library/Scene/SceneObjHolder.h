#pragma once

#include <al/Library/Scene/ISceneObj.h>

namespace al {
class ActorInitInfo;

class SceneObjHolder {
private:
    al::ISceneObj* (*mCreator)(s32);
    al::ISceneObj** mSceneObjArray;
    s32 mArraySize;

public:
    SceneObjHolder(al::ISceneObj* (*)(s32), s32);
    al::ISceneObj* create(s32);
    al::ISceneObj* tryGetObj(s32) const;
    al::ISceneObj* getObj(s32) const;
    bool isExist(s32) const;
    void setSceneObj(al::ISceneObj*, s32);
    void initAfterPlacementSceneObj(const al::ActorInitInfo&);
};

class IUseSceneObjHolder {
private:
    static const char* sSceneObjName;

public:
    virtual al::SceneObjHolder* getSceneObjHolder() const = 0;
};

al::ISceneObj* createSceneObj(al::IUseSceneObjHolder const*,int);
void setSceneObj(al::IUseSceneObjHolder const*,al::ISceneObj *,int);
al::ISceneObj* getSceneObj(al::IUseSceneObjHolder const*,int);
al::ISceneObj* tryGetSceneObj(al::IUseSceneObjHolder const*,int);
bool isExistSceneObj(al::IUseSceneObjHolder const*,int);
void deleteSceneObj(al::IUseSceneObjHolder const*,int);
void tryDeleteSceneObj(al::IUseSceneObjHolder const*,int);

}
