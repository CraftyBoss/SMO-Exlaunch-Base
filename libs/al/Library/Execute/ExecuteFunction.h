#pragma once

#include <al/Library/Execute/ExecuteDirector.h>

namespace al {
    void registerExecutorActorUpdate(al::LiveActor *,al::ExecuteDirector *,char const*);
    void registerExecutorActorDraw(al::LiveActor *,al::ExecuteDirector *,char const*);
    void registerExecutorLayoutUpdate(al::LayoutActor *,al::ExecuteDirector *,char const*);
    void registerExecutorLayoutDraw(al::LayoutActor *,al::ExecuteDirector *,char const*);
    void registerExecutorUser(al::IUseExecutor *,al::ExecuteDirector *,char const*);
    void registerExecutorFunctor(char const*,al::ExecuteDirector *,al::FunctorBase const&);
    void registerExecutorFunctorDraw(char const*,al::ExecuteDirector *,al::FunctorBase const&);
}

namespace alActorSystemFunction {
    void addToExecutorMovement(al::LiveActor *);
    void addToExecutorDraw(al::LiveActor *);
    void removeFromExecutorMovement(al::LiveActor *);
    void removeFromExecutorDraw(al::LiveActor *);
    void updateExecutorDraw(al::LiveActor *);
}

void sub_7100893AA4();

namespace alExecuteFunction {
    void updateEffect(al::ExecuteDirector const*);
    void updateEffectSystem(al::ExecuteDirector const*);
    void updateEffectPlayer(al::ExecuteDirector const*);
    void updateEffectDemo(al::ExecuteDirector const*);
    void updateEffectLayout(al::ExecuteDirector const*);
}
