#pragma once

namespace al {
  struct LiveActor;
}

namespace al {
class ExecuteRequestKeeper {
public:
    void* mActorMovementAllOn; // 0x0
    void* mActorMovementAllOff; // 0x8
    void* mActorDrawAllOn; // 0x10
    void* mActorDrawAllOff; // 0x18
public:
    ExecuteRequestKeeper(int);
    void executeRequestActorMovementAllOn();
    void executeRequestActorMovementAllOff();
    void executeRequestActorDrawAllOn();
    void executeRequestActorDrawAllOff();
    void request(al::LiveActor*, int);
};
}