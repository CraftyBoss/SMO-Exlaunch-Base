#pragma once

#include <al/Library/Thread/FunctorV0M.h>

#include "IUseExecutor.h"
#include "ExecuteSystemInitInfo.h"
#include "ExecuteRequestKeeper.h"
#include "ExecuteTableHolderDraw.h"
#include "ExecuteTableHolderUpdate.h"

namespace al {
class ExecuteDirector {
private:
    int mRequestCount = 0;
    int mUpdateTableCount = 0;
    al::ExecuteTableHolderUpdate **mUpdateTables = nullptr;
    int mDrawTableCount = 0;
    al::ExecuteTableHolderDraw **mDrawTables = nullptr;
    al::ExecuteRequestKeeper *mRequestKeeper = nullptr;
public:
    ExecuteDirector(int count);
    virtual ~ExecuteDirector();
    void init(al::ExecuteSystemInitInfo const&);
    void registerActorUpdate(al::LiveActor*, char const*);
    void registerActorDraw(al::LiveActor*, char const*);
    void registerActorModelDraw(al::LiveActor*, char const*);
    void registerLayoutUpdate(al::LayoutActor*, char const*);
    void registerLayoutDraw(al::LayoutActor*, char const*);
    void registerUser(al::IUseExecutor*, char const*);
    void registerFunctor(al::FunctorBase const&, char const*);
    void registerFunctorDraw(al::FunctorBase const&, char const*);
    void createExecutorListTable();
    void execute(char const*) const;
    void executeList(char const*, char const*) const;
    void draw(char const*) const;
    void drawList(char const*, char const*) const;
    bool isActiveDraw(char const*) const;
};
}
