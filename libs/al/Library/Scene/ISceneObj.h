#pragma once


namespace al {
class ActorInitInfo;

class ISceneObj {
public:
    virtual const char* getSceneObjName() {return "";}
    virtual ~ISceneObj() = default;
    virtual void initAfterPlacementSceneObj(al::ActorInitInfo const&) {}
    virtual void initSceneObj() {}
};
}