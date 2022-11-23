#pragma once

#include "imgui.h"
#include "nvn.h"
#include "nvn_Cpp.h"
#include "nvn_CppMethods.h"

#ifdef __cplusplus

namespace ImguiNvnBackend {

    struct NvnBackendData {

        // general data

        nvn::Device *device;
        nvn::Queue *queue;
        nvn::CommandBuffer *cmdBuf;

        // shader data

        nvn::Program shaderProgram;
        nvn::MemoryPoolBuilder memPoolBuilder;
        nvn::MemoryPool bufferPool;
        
        nvn::BufferBuilder bufferBuilder;

        nvn::Buffer vertShaderBuffer;
        nvn::Buffer fragShaderBuffer;
    };

    void setupShaders(void* vertShaderBinary, void* fragShaderBinary);
    void InitBackend(nvn::Device* device, nvn::Queue* queue, nvn::CommandBuffer* cmdBuf);
    void ShutdownBackend();

    void LoadShaders();

    void newFrame();
    void renderDrawData(ImDrawData *drawData);

    NvnBackendData* getBackendData();
}; // namespace ImguiNvnBackend

#endif
