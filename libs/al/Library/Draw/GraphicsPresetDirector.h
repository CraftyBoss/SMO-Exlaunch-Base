#pragma once

#include <al/Library/Resource/Resource.h>
#include <container/seadPtrArray.h>
#include "GraphicsPreset.h"

namespace al {
    class GraphicsSystemInfo;

    class GraphicsPresetDirector {
    public:
        struct GraphicsRequest { // guessed name
            bool mIsUsed;
            int pad;
            sead::FixedSafeString<0x40> mPresetName;
            int unkInt1;
            int LerpStep;
            int LerpStepOut;
            sead::Vector3f mBaseAngle;
        };
    private:
        GraphicsSystemInfo *mSystemInfo;
        Resource *mResGraphicsPreset;
        sead::PtrArray<GraphicsPreset> mPresetList;
        GraphicsPreset *mCurrentPreset;
        GraphicsPreset *mPrevPreset;
        sead::PtrArray<GraphicsRequest> mRequestList;
        GraphicsRequest mNextRequest;
        GraphicsRequest mCurRequest;
        int unkInt9;
    public:
        GraphicsPresetDirector(al::GraphicsSystemInfo *);

        void calcPresetNum(void);

        void clearRequest(void);

        void endInit(void);

        void findDefaultPreset(void);

        void findPreset(char const *);

        void findPreset(int);

        void findPresetId(char const *);

        void initProjectResource(void);

        void registerPreset(char const *, char const *, char const *, bool);

        void requestPreset(char const *, int, int, int, sead::Vector3f const &);

        void update(void);
    };
}