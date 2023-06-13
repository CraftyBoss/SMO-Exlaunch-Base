#pragma once

#include <al/Library/Thread/FunctorV0M.h>

#include <al/Library/Execute/ExecuteOrder.h>
#include <al/Library/Execute/ExecuteSystemInitInfo.h>
#include <al/Library/Execute/ExecuteTable.h>
#include <al/Library/Execute/ExecutorListBase.h>
#include <al/Library/Execute/IUseExecutor.h>

#include <container/seadPtrArray.h>

namespace al {
    struct ExecutorListActorExecuteBase;
    struct ExecutorListLayoutUpdate;
    struct ExecutorListIUseExecutorUpdate;
    struct ExecutorListFunctor;
    struct LiveActor;
    struct LayoutActor;
}

namespace al {
class ExecuteTableHolderUpdate {
private:
    const char* mName;
    sead::PtrArray<al::ExecutorListBase> mActiveExecutors;
    sead::PtrArray<al::ExecutorListBase> mExecutorsAll;
    sead::PtrArray<al::ExecutorListActorExecuteBase> mExecutorsActor;
    sead::PtrArray<al::ExecutorListLayoutUpdate> mExecutorsLayout;
    sead::PtrArray<al::ExecutorListIUseExecutorUpdate> mExecutorsUser;
    sead::PtrArray<al::ExecutorListFunctor> mExecutorsFunctor;
public:
    ExecuteTableHolderUpdate();
    virtual ~ExecuteTableHolderUpdate();
    void init(char const*, al::ExecuteSystemInitInfo const&, al::ExecuteOrder const*, int);
    void registerExecutorListActor(al::ExecutorListActorExecuteBase*);
    void registerExecutorListLayout(al::ExecutorListLayoutUpdate*);
    void registerExecutorListUser(al::ExecutorListIUseExecutorUpdate*);
    void registerExecutorListFunctor(al::ExecutorListFunctor*);
    void registerExecutorListAll(al::ExecutorListBase*);
    void tryRegisterActor(al::LiveActor*, char const*);
    void tryRegisterLayout(al::LayoutActor*, char const*);
    void tryRegisterUser(al::IUseExecutor*, char const*);
    void tryRegisterFunctor(al::FunctorBase const&, char const*);
    void createExecutorListTable();
    void execute() const;
    void executeList(char const*) const;

    const char* getName() { return mName; }
};
}  // namespace al
