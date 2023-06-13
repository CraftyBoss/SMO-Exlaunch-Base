#pragma once

#include <al/Library/LiveActor/LiveActor.h>

namespace al {
class SilhouetteModel : public al::LiveActor {
public:
    SilhouetteModel(al::LiveActor*, const al::ActorInitInfo&, const char*);
    void movement() override;
};
}
