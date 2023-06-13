#pragma once

#include <al/Library/Thread/FunctorV0M.h>

#include <al/Library/Execute/ExecuteOrder.h>
#include <al/Library/Execute/ExecuteSystemInitInfo.h>
#include <al/Library/Execute/ExecuteTable.h>
#include <al/Library/Execute/ExecutorListBase.h>
#include <al/Library/Execute/IUseExecutor.h>

#include <container/seadPtrArray.h>

namespace al {
    struct ExecutorListActorModelDrawBase;
    struct ExecutorListActorDraw;
    struct ExecutorListLayoutDrawBase;
    struct ExecutorListIUseExecutorDraw;
    struct ExecutorListFunctor;
    struct LiveActor;
    struct LayoutActor;
}

namespace al {
class ExecuteTableHolderDraw {
private:
    const char* mName;
    sead::PtrArray<al::ExecutorListBase> mActiveExecutors;
    sead::PtrArray<al::ExecutorListBase> mExecutorsAll;
    sead::PtrArray<al::ExecutorListActorDraw> mExecutorsActor;
    sead::PtrArray<al::ExecutorListActorModelDrawBase> mExecutorsActorModel;
    sead::PtrArray<al::ExecutorListLayoutDrawBase> mExecutorsLayout;
    sead::PtrArray<al::ExecutorListIUseExecutorDraw> mExecutorsUser;
    sead::PtrArray<al::ExecutorListFunctor> mExecutorsFunctor;
public:
    ExecuteTableHolderDraw();
    virtual ~ExecuteTableHolderDraw();
    void init(char const*, al::ExecuteSystemInitInfo const&, al::ExecuteOrder const*, int);
    void registerExecutorListActorModel(al::ExecutorListActorModelDrawBase*);
    void registerExecutorListActor(al::ExecutorListActorDraw*);
    void registerExecutorListLayout(al::ExecutorListLayoutDrawBase*);
    void registerExecutorListUser(al::ExecutorListIUseExecutorDraw*);
    void registerExecutorListFunctor(al::ExecutorListFunctor*);
    void registerExecutorListAll(al::ExecutorListBase*);
    void tryRegisterActor(al::LiveActor*, char const*);
    void tryRegisterActorModel(al::LiveActor*, char const*);
    void tryRegisterLayout(al::LayoutActor*, char const*);
    void tryRegisterUser(al::IUseExecutor*, char const*);
    void tryRegisterFunctor(al::FunctorBase const&, char const*);
    void createExecutorListTable();
    void execute() const;
    void executeList(char const*) const;
    bool isActive() const;

    const char* getName() { return mName; }
};
}