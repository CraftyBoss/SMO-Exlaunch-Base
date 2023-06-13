#pragma once

#include <al/Library/Thread/AsyncFunctorThread.h>
#include <al/Library/HostIO/HioNode.h>

#include <heap/seadFrameHeap.h>

class WorldResourceLoader : public al::HioNode {
public:
    WorldResourceLoader(GameDataHolder *);
    virtual ~WorldResourceLoader();
    void loadResource(void);
    void cancelLoadWorldResource(void);
    void tryDestroyWorldResource(void);
    bool requestLoadWorldHomeStageResource(int worldIndex, int scenario);
    bool isEndLoadWorldResource(void) const;
    void requestLoadWorldResourceCommon(int);
    void requestLoadWorldResource(int);
    void createResourcePlayer(void);
    void tryDestroyWorldResourceOnlyCap(void);
    float calcLoadPercent(void) const;
    int getLoadWorldId(void);
    bool tryLoadResource(char const*,char const*,char const*);
    void loadWorldResource(int,int,bool,char const*);
    float calcWorldResourceHeapSize(void) const;

    al::AsyncFunctorThread *mWorldResourceLoader; // WorldResourceLoader::loadResource
    sead::FrameHeap *mWorldResourceHeap;
    sead::FrameHeap *mCapWorldHeap;
    sead::FrameHeap *mWaterfallWorldHeap;
    int mLoadWorldId;
    int mScenarioNo;
    bool mIsScenarioRes;
    bool unkBool2;
    void *unkPtr4;
    void *unkPtr5;
    int unkInt3;
    bool mIsLoadResTable;
    int mCurLoadCount;
    int mMaxLoadCount;
    GameDataHolder *mDataHolder;
    bool unkBool4;
    int unkInt6;
};

static_assert(sizeof(WorldResourceLoader) == 0x68, "WorldResourceLoader Size");