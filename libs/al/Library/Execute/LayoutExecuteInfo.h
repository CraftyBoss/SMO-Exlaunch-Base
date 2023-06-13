#pragma once

namespace al {

class ExecutorListLayoutUpdate;
class ExecutorListLayoutDrawBase;

class LayoutExecuteInfo {
private:
    int mUpdaterCount = 0;
    al::ExecutorListLayoutUpdate *mUpdaters[2] = {};
    int mDrawerCount = 0;
    al::ExecutorListLayoutDrawBase *mDrawers[4] = {};
public:
    LayoutExecuteInfo(void);
    void addUpdater(al::ExecutorListLayoutUpdate *);
    void addDrawer(al::ExecutorListLayoutDrawBase *);
};

}  // namespace al