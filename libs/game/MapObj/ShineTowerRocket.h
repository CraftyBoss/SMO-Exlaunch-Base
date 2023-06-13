#pragma once

#include <al/Library/LiveActor/LiveActor.h>
#include "IUseDemoSkip.h"

namespace al {
    class IEventFlowEventReceiver {};
}

class ShineTowerRocket : public al::LiveActor, public al::IEventFlowEventReceiver, public IUseDemoSkip {
    // virtual void makeActorDead 0x30
};