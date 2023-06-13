#pragma once

#include <al/Library/LiveActor/LiveActor.h>

namespace al {
class ModelDrawParts : public LiveActor {
private:
public:
    ModelDrawParts(char const*,al::LiveActor const*,al::ActorInitInfo const&,char const*);
};
static_assert(sizeof(ModelDrawParts) == 0x108, "ModelDrawParts Size");
}
