#pragma once

#include <al/Library/Yaml/ParameterObj.h>
#include <al/Library/Yaml/ParameterList.h>
#include <al/Library/Yaml/IUseRequestParam.h>
#include <al/Library/Resource/Resource.h>
#include "al/Project/Draw/GraphicsAreaDirector.h"

namespace agl::utl {
    class IParameterObj {
        char size[0x30];
    };

    class IParameterList {
        char size[0x40];
    };

    class IParameterIO : public IParameterList {
        char size[0x190];
    };

    class ParameterBase {
        char size[0x18];
    };

    template<class T>
    class __attribute__((aligned(8))) Parameter : ParameterBase {
        T mParam;
    };

    typedef Parameter<float> ParameterFloat;
    typedef Parameter<int> ParameterInt;
    typedef Parameter<bool> ParameterBool;
}

namespace al {
    class MaterialCategoryKeeper;

    class DirLightParam : IUseRequestParam {
    };

    class HdrParam : IUseRequestParam {
    };

    class MaterialCategoryParam : IUseRequestParam {
    };

    class FogParam : IUseRequestParam {
    };

    class YFogParam : IUseRequestParam {
    };

    class BloomParam : IUseRequestParam {
    };

    class SkyParam : IUseRequestParam {
    };

    class DepthOfFieldParam : IUseRequestParam {
    };

    class DepthShadowParam : IUseRequestParam {
    };

    class DepthShadowClipParam : IUseRequestParam {
    };

    class LightStreakParam : IUseRequestParam {
    };

    class FlareFilterParam : IUseRequestParam {
    };

    class GodRayParam : IUseRequestParam {
    };

    class MirrorParam : IUseRequestParam {
    };

    class VignettingParam : IUseRequestParam {
    };

    class ProgramTextureParam : IUseRequestParam {
    };

    class GraphicsPreset {
    private:
        bool mIsActive;
        al::ParameterObj *mParamObj;
        al::ParameterString64 *mNameParam;
        al::ParameterIo *mParamRoot;
        agl::utl::IParameterObj *mAglParamObj;
        agl::utl::ParameterBase mAglNameParam;
        sead::FixedSafeString<0x40> mString;
        agl::utl::IParameterIO *mAglParamIo;
        al::DirLightParam *mDirLightParam;
        al::HdrParam *mHdrParam;
        al::MaterialCategoryParam *mMatCategoryParam;
        al::FogParam *mFogParam;
        al::YFogParam *mYFogParam;
        al::BloomParam *mBloomParam;
        al::SkyParam *mSkyParam;
        al::DepthOfFieldParam *mDoFParam;
        al::DepthShadowParam *mDepthShadowParam;
        al::DepthShadowClipParam *mDepthShadowClipParam;
        al::LightStreakParam *mLightStreakParam;
        al::FlareFilterParam *mFlareFilterParam;
        al::GodRayParam *mGodRayParam;
        al::MirrorParam *mMirrorParam;
        al::VignettingParam *mVignettingParam;
        al::ProgramTextureParam *mProgramTexParam;
        void *mPresetCCData;
        void *mPresetShadowParamData;
        void *mPresetSSAOData;
    public:
        GraphicsPreset(char const *, al::Resource const *);

        void endInit(al::MaterialCategoryKeeper *, al::GraphicsAreaDirector const *);

        const char *getName(void) const;
    };
}