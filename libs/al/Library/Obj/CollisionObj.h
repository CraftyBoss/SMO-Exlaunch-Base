#pragma once

#include <al/Library/LiveActor/LiveActor.h>
#include <al/Library/Resource/Resource.h>

namespace al {
class CollisionObj : public al::LiveActor {
private:

public:
    CollisionObj(const al::ActorInitInfo&, al::Resource*, const char*, al::HitSensor *,const sead::Matrix34f*, const char*);
};
static_assert(sizeof(CollisionObj) == 0x108, "CollisionObj Size");

CollisionObj *createCollisionObj(al::LiveActor const*,al::ActorInitInfo const&,char const*,al::HitSensor *,char const*,char const*);
CollisionObj *createCollisionObjMtx(al::LiveActor const*,al::ActorInitInfo const&,char const*,al::HitSensor *,sead::Matrix34f const*,char const*);
}
