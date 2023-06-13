#pragma once

#include <al/Library/HostIO/HioNode.h>
#include <al/Library/Model/ModelCtrl.h>
#include <al/Library/Model/ModelKeeper.h>

#include <basis/seadTypes.h>

namespace agl {
class DrawContext;
}

namespace al {

class GraphicsSystemInfo;
class ModelDrawBufferCounter;
class ModelDrawDisplayList;

class ModelDrawerBase : public al::HioNode {
private:
    const char *mName;
    agl::DrawContext *mDrawCtx;
    const al::ModelKeeper *mModelKeeper;
    const al::GraphicsSystemInfo *mGraphicsSystemInfo;
    const al::ModelDrawBufferCounter *mModelDrawBufferCounter;
    al::ModelDrawDisplayList *mDrawDisplayList;
    s32 mCapacity;
    s32 mSize;
    al::ModelCtrl **mMdlCtrls;
    void* field_48;
public:
    void createTable(void);

    virtual void registerModel(al::ModelCtrl *);
    virtual void addModel(al::ModelCtrl *);
    virtual void removeModel(al::ModelCtrl *);
    virtual void updateModel(al::ModelCtrl *);

    void setDrawInfo(agl::DrawContext *,al::GraphicsSystemInfo const*,al::ModelDrawBufferCounter const*,al::ModelKeeper const*);
    void addModelToTable(al::ModelCtrl *);
    void getDrawBufferIndex(void);
    void createModelDrawDisplayList(int);
    bool isDraw(void) const;
};
}