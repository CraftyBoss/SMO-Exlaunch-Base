#pragma once

#include <al/Library/Model/ModelCtrl.h>
#include <al/Library/Resource/Resource.h>

#include <math/seadMatrix.h>

namespace al {
    class ModelLodCtrl;
    class DitherAnimator;
    class GpuMemAllocator;
    class ModelShaderHolder;
    class ModelOcclusionCullingDirector;
    class ShadowDirector;
    class PrepassTriangleCulling;
}

namespace al {
    class ModelKeeper {
    private:
        const char *mResourceName;
        al::ModelCtrl *mModelCtrl;
        const al::ActorResource *mResource;
        char gap20[67];
        bool field_63;
    public:
        ModelKeeper();
        virtual ~ModelKeeper();
        void initResource(al::ActorResource const*);
        void createMatAnimForProgram(int);
        void getAnimResource() const;
        void getModelResource() const;
        void setDisplayRootJointMtxPtr(sead::Matrix34f const*);
        void setModelLodCtrl(al::ModelLodCtrl*);
        void setDitherAnimator(al::DitherAnimator*);
        void initModel(int, al::GpuMemAllocator*, al::ModelShaderHolder*, al::ModelOcclusionCullingDirector*, al::ShadowDirector*, al::PrepassTriangleCulling*);
        void show();
        void hide();
        void update();
        void updateLast();
        void calc(sead::Matrix34f const&, sead::Vector3f const&);
        void getBaseMtx() const;
        void getWorldMtxPtrByIndex(int) const;
   };
}