#pragma once

#include <agl/DrawContext.h>
#include <al/Library/Base/String.h>
#include "GraphicsPresetDirector.h"

namespace al {
    class ShadowDirector;

    class ShaderMirrorDirector;

    class MaterialLightDirector;

    class SkyDirector;

    class GpuMemAllocator;

    class SubCameraRenderer;

    class ModelOcclusionCullingDirector;

    class ModelShaderHolder;

    class PrepassTriangleCulling;

    struct GraphicsParamFilePath {
        GraphicsParamFilePath(char const *, char const *);

        void makeBinaryPath(al::StringTmp<0x100> *);

        sead::FixedSafeString<0x100> mFileName;
        sead::FixedSafeString<0x100> mExt;
    };

    class GraphicsSystemInfo {
    public:
        void *qword0;
        void *qword8;
        void *qword10;
        void *qword18;
        char gap20[5];
        char byte25;
        char byte26;
        char byte27;
        int mDisplayWidth;
        int mDisplayHeight;
        int dword30;
        int dword34;
        int dword38;
        int dword3C;
        char byte40;
        int dword44;
        char byte48;
        int dword4C;
        int dword50;
        int dword54;
        int dword58;
        int dword5C;
        agl::DrawContext *mDrawCtx;
        char char68;
        void *field_70; // al::ShaderCubeMapKeeper* at 0x0
        void *qword78;
        void *qword80;
        al::GraphicsPresetDirector *mPresetDirector;
        char gap90[32];
        al::ShadowDirector *mShadowDirector;
        char gapB8[16];
        al::ShaderMirrorDirector *field_C8;
        char gapD0[320];
        char char210;
        void *qword218;
        void *qword220;
        void *qword228;
        al::MaterialLightDirector *mMatLightDirector;
        void *qword238;
        al::SkyDirector *mSkyDirector;
        void *qword248;
        void *qword250;
        void *qword258;
        void *qword260;
        void *qword268;
        void *qword270;
        void *qword278;
        void *qword280;
        al::GpuMemAllocator *mGpuMemAllocator;
        char gap290[8];
        void *qword298;
        void *qword2A0;
        char gap2A8[8];
        void *qword2B0;
        al::SubCameraRenderer *field_2B8;
        void *qword2C0;
        void *qword2C8;
        void *qword2D0;
        void *qword2D8;
        void *qword2E0;
        void *qword2E8;
        int dword2F0;
        __attribute__((packed)) __attribute__((aligned(1))) void *qword2F4;
        __attribute__((packed)) __attribute__((aligned(1))) void *qword2FC;
        __attribute__((packed)) __attribute__((aligned(1))) void *qword304;
        int dword30C;
        al::GraphicsParamFilePath *mParamFilePath;
        agl::utl::IParameterIO mRootListParam;
        agl::utl::IParameterObj mGraphicsSystemParam;
        agl::utl::ParameterInt mAreaFindModeParam;
        agl::utl::ParameterInt mAtmosScatterTypeParam;
        agl::utl::ParameterBool mIsUsingUpdateAtmosCubeMapParam;
        agl::utl::ParameterBool mIsUsingOceanWaveParam;
        agl::utl::ParameterInt mOccGroupNumParam;
        agl::utl::IParameterIO mRootParam;
        agl::utl::IParameterObj mProjectParam;
        agl::utl::ParameterBool mIsUsingTemporalParam;
        agl::utl::ParameterBool mIsUsingPeripheryParam;
        agl::utl::ParameterBool mIsUsingStarrySkyParam;
        agl::utl::ParameterFloat mCubeMapIntensityPowerParam;
        agl::utl::ParameterFloat mCubeMapIntensityRangeParam;
        agl::utl::ParameterFloat mLineLightAntiArtifactParam;
        agl::utl::ParameterFloat mMinRoughnessGGXParam;
        agl::utl::ParameterFloat mSphereLightDiffuseAddParam;
        agl::utl::ParameterFloat mSpecularScaleParam;
        agl::utl::ParameterFloat mLightUnitScaleParam;
        agl::utl::ParameterFloat mLightColorScaleParam;
        void *qword918;
        void *qword920;
        void *qword928;
        void *qword930;
        void *qword938;
        void *qword940;
        void *qword948;
        void *qword950;
        void *qword958;
        int dword960;
        void *qword968;
        void *qword970;
        int dword978;
        void *qword980;
        al::ModelOcclusionCullingDirector *mOcclusionDirector;
        void *qword990;
        al::ModelShaderHolder *mModelShaderHolder;
        al::PrepassTriangleCulling *field_9A0;
        char byte9A8;
        void *field_9B0;
    };
}