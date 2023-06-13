#pragma once

#include <al/Library/Model/ModelDrawerBase.h>
#include <al/Library/Execute/ExecuteRequestKeeper.h>
namespace al {

class ExecutorActorExecuteBase;

class ActorExecuteInfo {
private:
    al::ExecuteRequestKeeper *mRequestKeeper;
    int mUpdaterCount = 0;
    al::ExecutorActorExecuteBase *mUpdaters[4] = {};
    int mDrawerCount = 0;
    al::ModelDrawerBase *mDrawers[11] = {};
public:
    ActorExecuteInfo(al::ExecuteRequestKeeper* keeper);
    void addUpdater(al::ExecutorActorExecuteBase* updater);
    void addDrawer(al::ModelDrawerBase* drawer);
};

}  // namespace al