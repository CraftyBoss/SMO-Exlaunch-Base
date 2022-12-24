#pragma once

#define IMGUI_USER_CONFIG "imgui_backend/nvn_imgui_config.h"

#include "ImguiShaderCompiler.h"
#include "imgui.h"
#include "nvn_Cpp.h"
#include "nvn_CppMethods.h"
#include "types.h"
#include "MemoryBuffer.h"

#ifdef __cplusplus

namespace ImguiNvnBackend {

    struct NvnBackendInitInfo {
        nvn::Device *device;
        nvn::Queue *queue;
        nvn::CommandBuffer *cmdBuf;
        nvn::TexturePool *texPool;
        nvn::SamplerPool *samplerPool;
    };

    struct NvnBackendData {

        // general data

        nvn::Device *device;
        nvn::Queue *queue;
        nvn::CommandBuffer *cmdBuf;
        nvn::TexturePool *texPool;
        nvn::SamplerPool *samplerPool;

        // builders

        nvn::BufferBuilder bufferBuilder;
        nvn::MemoryPoolBuilder memPoolBuilder;
        nvn::TextureBuilder texBuilder;

        // shader data

        nvn::Program shaderProgram;

        MemoryBuffer *shaderMemory;
        MemoryBuffer *uniformMemory;

        nvn::ShaderData shaderDatas[2]; // 0 - Vert 1 - Frag

        nvn::VertexStreamState streamState;
        nvn::VertexAttribState attribStates[3];

        // font data

        nvn::MemoryPool fontMemPool;

        int samplerId;
        nvn::Sampler fontSampler;
        int textureId;
        nvn::Texture fontTexture;

        nvn::TextureHandle fontTexHandle;

        // render data

        MemoryBuffer *vtxBuffer;
        MemoryBuffer *idxBuffer;

        // misc data

        u64 lastTick;
        bool isInitialized;

        CompiledData imguiShaderBinary;

        // test shader data

        bool isUseTestShader = false;
        nvn::Program testShader;
        nvn::ShaderData testShaderDatas[2]; // 0 - Vert 1 - Frag
        MemoryBuffer *testShaderBuffer;
        CompiledData testShaderBinary;
    };

    bool createShaders();

    bool setupShaders(u8 *shaderBinary, ulong binarySize);

    bool setupFont();

    void InitBackend(const NvnBackendInitInfo &initInfo);

    void ShutdownBackend();

    void updateInput();

    void newFrame();

    void renderDrawData(ImDrawData *drawData);

    NvnBackendData *getBackendData();
}; // namespace ImguiNvnBackend

#endif
