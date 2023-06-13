#pragma once

#include <al/Library/LiveActor/LiveActor.h>

namespace al {
class DepthShadowModel : public LiveActor {
private:
    void *field_108;
    int field_110;
    bool field_114;
public:
    DepthShadowModel(al::LiveActor *,al::ActorInitInfo const&,char const*,bool);
    DepthShadowModel(al::LiveActor *,al::ActorInitInfo const&,char const*,char const*,bool);
    void initAfterPlacement() override;
};
static_assert(sizeof(DepthShadowModel) == 0x118, "DepthShadowModel Size");
}
