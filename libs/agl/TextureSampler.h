#pragma once

#include "agl/detail/Surface.h"
#include "agl/driver/NVNtexture.h"
#include "agl/util.h"
#include "TextureData.h"
#include <prim/seadSafeString.h>

namespace agl {
    class TextureSampler {
    public:
        void *unk1;
        TextureData mTextureData;
        char unk2[0x40];
    };
};