#include "imgui_impl_nvn.hpp"
#include "lib.hpp"
#include "helpers.h"
#include "logger/Logger.hpp"

#include "nn/os.h"
#include "nn/hid.h"

#include "tenacity_font.h"
#include "helpers/InputHelper.h"

#define UBOSIZE 0x1000

#define DISPWIDTH 1280.0f
#define DISPHEIGHT 720.0f

typedef float Matrix44f[4][4];

// orthographic matrix used for shader
static const Matrix44f projMatrix = {
        {0.001563f, 0.0f,       0.0f,  0.0f},
        {0.0f,      -0.002778f, 0.0f,  0.0f},
        {0.0f,      0.0f,       -0.5f, 0.0f},
        {-1.0f,     1.0f,       0.5f,  1.0f}
};

namespace ImguiNvnBackend {

    ImVector<ImVec2> shaderTesting(int X, int Y) {

        // Define the size of each quad in the X and Y direction
        float quadSizeX = 1.0f;
        float quadSizeY = 1.0f;

        // Create a vector to store the vertices of the plane
        ImVector<ImVec2> vertices;
        vertices.resize(6);

        // Loop over the X and Y dimensions of the grid
        for (int i = 0; i < X; i++) {
            for (int j = 0; j < Y; j++) {
                // Compute the position of the four vertices of the quad
                ImVec2 p1 = ImVec2(i * quadSizeX, j * quadSizeY);
                ImVec2 p2 = ImVec2(i * quadSizeX + quadSizeX, j * quadSizeY);
                ImVec2 p3 = ImVec2(i * quadSizeX, j * quadSizeY + quadSizeY);
                ImVec2 p4 = ImVec2(i * quadSizeX + quadSizeX, j * quadSizeY + quadSizeY);

                // Add the vertices of the quad to the vector of vertices
                vertices.push_back(p1);
                vertices.push_back(p2);
                vertices.push_back(p3);

                vertices.push_back(p2);
                vertices.push_back(p4);
                vertices.push_back(p3);
            }
        }

        return vertices;
    }

    void initTestShader() {

        auto bd = getBackendData();
        bd->testShaderBinary = ImguiShaderCompiler::CompileShader("test");

        bd->testShaderBuffer = IM_NEW(MemoryBuffer)(bd->testShaderBinary.size, bd->testShaderBinary.ptr,
                                                    nvn::MemoryPoolFlags::CPU_UNCACHED |
                                                    nvn::MemoryPoolFlags::GPU_CACHED |
                                                    nvn::MemoryPoolFlags::SHADER_CODE);

        EXL_ASSERT(bd->testShaderBuffer->IsBufferReady(), "Shader Buffer was not ready! unable to continue.");

        BinaryHeader offsetData = BinaryHeader((u32 *) bd->testShaderBinary.ptr);

        nvn::BufferAddress addr = bd->testShaderBuffer->GetBufferAddress();

        nvn::ShaderData &vertShaderData = bd->testShaderDatas[0];
        vertShaderData.data = addr + offsetData.mVertexDataOffset;
        vertShaderData.control = bd->testShaderBinary.ptr + offsetData.mVertexControlOffset;

        nvn::ShaderData &fragShaderData = bd->testShaderDatas[1];
        fragShaderData.data = addr + offsetData.mFragmentDataOffset;
        fragShaderData.control = bd->testShaderBinary.ptr + offsetData.mFragmentControlOffset;

        EXL_ASSERT(bd->testShader.Initialize(bd->device), "Unable to Init Program!");
        EXL_ASSERT(bd->testShader.SetShaders(2, bd->testShaderDatas), "Unable to Set Shaders!");

        Logger::log("Test Shader Setup.\n");


    }

    void renderTestShader() {

        auto bd = getBackendData();

        int pointCount = 3;

        size_t totalVtxSize = pointCount * sizeof(ImVec2);
        if (!bd->vtxBuffer || bd->vtxBuffer->GetPoolSize() < totalVtxSize) {
            if (bd->vtxBuffer) {
                bd->vtxBuffer->Finalize();
                IM_FREE(bd->vtxBuffer);
            }
            bd->vtxBuffer = IM_NEW(MemoryBuffer)(totalVtxSize);
            Logger::log("(Re)sized Vertex Buffer to Size: %d\n", totalVtxSize);
        }

        if (!bd->vtxBuffer->IsBufferReady()) {
            Logger::log("Cannot Draw Data! Buffers are not Ready.\n");
            return;
        }

        ImVec2 *verts = (ImVec2 *) bd->vtxBuffer->GetMemPtr();

        verts[0] = ImVec2(300, 300);
        verts[1] = ImVec2(400, 400);
        verts[2] = ImVec2(300, 400);

        bd->cmdBuf->BeginRecording();
        bd->cmdBuf->BindProgram(&bd->testShader, nvn::ShaderStageBits::VERTEX | nvn::ShaderStageBits::FRAGMENT);

        bd->cmdBuf->BindUniformBuffer(nvn::ShaderStage::VERTEX, 0, *bd->uniformMemory, UBOSIZE);
        bd->cmdBuf->UpdateUniformBuffer(*bd->uniformMemory, UBOSIZE, 0, sizeof(projMatrix), &projMatrix);

        nvn::VertexAttribState attribute;
        attribute.SetDefaults().SetFormat(nvn::Format::RG32F, 0).SetStreamIndex(0);

        nvn::VertexStreamState stream;
        stream.SetDefaults();
        stream.SetStride(sizeof(ImVec2));

        bd->cmdBuf->BindVertexAttribState(1, &attribute);
        bd->cmdBuf->BindVertexStreamState(1, &stream);
        bd->cmdBuf->BindVertexBuffer(0, (*bd->vtxBuffer), bd->vtxBuffer->GetPoolSize());

        bd->cmdBuf->DrawArrays(nvn::DrawPrimitive::TRIANGLES, 0, pointCount);

        auto handle = bd->cmdBuf->EndRecording();
        bd->queue->SubmitCommands(1, &handle);
    }

// backend impl

    NvnBackendData *getBackendData() {
        NvnBackendData *result = ImGui::GetCurrentContext() ? (NvnBackendData *) ImGui::GetIO().BackendRendererUserData
                                                            : nullptr;
        EXL_ASSERT(result, "Backend has not been initialized!");
        return result;
    }

    bool createShaders() {

        auto bd = getBackendData();

        if (ImguiShaderCompiler::CheckIsValidVersion(bd->device)) {
            Logger::log("GLSLC compiler can be used!\n");

            ImguiShaderCompiler::InitializeCompiler();

            bd->imguiShaderBinary = ImguiShaderCompiler::CompileShader("imgui");

        } else {
            Logger::log("Unable to compile shaders at runtime. falling back to pre-compiled shaders.\n");

            FsHelper::LoadData loadData = {
                    .path = "sd:/smo/shaders/imgui.bin"
            };

            FsHelper::loadFileFromPath(loadData);

            bd->imguiShaderBinary.size = loadData.bufSize;
            bd->imguiShaderBinary.ptr = (u8 *) loadData.buffer;
        }

        if (bd->imguiShaderBinary.size > 0) {
            return true;
        }

        return false;
    }

    bool setupFont() {

        Logger::log("Setting up ImGui Font.\n");

        auto bd = getBackendData();

        ImGuiIO &io = ImGui::GetIO();

        unsigned char *pixels;
        int width, height, pixelByteSize;
        io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height, &pixelByteSize);

        int texPoolSize = pixelByteSize * width * height;

        void *texturePool = IM_ALLOC(ALIGN_UP(texPoolSize, 0x1000));

        bd->memPoolBuilder.SetDefaults().SetDevice(bd->device).SetFlags(
                        nvn::MemoryPoolFlags::CPU_NO_ACCESS | nvn::MemoryPoolFlags::GPU_CACHED)
                .SetStorage(texturePool, ALIGN_UP(texPoolSize, 0x1000));

        if (!bd->fontMemPool.Initialize(&bd->memPoolBuilder)) {
            Logger::log("Failed to Create Font Memory Pool!\n");
            return false;
        }

        bd->texBuilder.SetDefaults()
                .SetDevice(bd->device)
                .SetTarget(nvn::TextureTarget::TARGET_2D)
                .SetFormat(nvn::Format::RGBA8UI)
                .SetSize2D(width, height)
                .SetStorage(&bd->fontMemPool, 0);

        if (!bd->fontTexture.Initialize(&bd->texBuilder)) {
            Logger::log("Failed to Create Font Texture!\n");
            return false;
        }

        // setup font texture

        void *scratchPool = IM_ALLOC(ALIGN_UP(texPoolSize, 0x1000));

        bd->memPoolBuilder.SetDefaults().SetDevice(bd->device).SetFlags(
                        nvn::MemoryPoolFlags::CPU_UNCACHED | nvn::MemoryPoolFlags::GPU_CACHED)
                .SetStorage(scratchPool, ALIGN_UP(texPoolSize, 0x1000));

        nvn::MemoryPool scratchMemPool;

        if (!scratchMemPool.Initialize(&bd->memPoolBuilder)) {
            Logger::log("Failed to Create Font Memory Pool!\n");
            return false;
        }

        memcpy(scratchMemPool.Map(), pixels, texPoolSize); // copy pixel data to memory pool

        bd->bufferBuilder.SetDefaults().SetDevice(bd->device)
                .SetStorage(&scratchMemPool, 0, ALIGN_UP(texPoolSize, 0x1000));

        nvn::Buffer scratchBuffer;
        if (!scratchBuffer.Initialize(&bd->bufferBuilder)) {
            Logger::log("Failed to Create Scratch Buffer!\n");
            return false;
        }

        nvn::TextureView view{};
        view.SetDefaults().SetTarget(nvn::TextureTarget::TARGET_2D).SetFormat(nvn::Format::RGBA8UI);

        nvn::CopyRegion region = {
                .xoffset = 0,
                .yoffset = 0,
                .zoffset = 0,
                .width = width,
                .height = height,
                .depth = 1
        };

//        bd->cmdBuf->BeginRecording();
//        bd->cmdBuf->CopyBufferToTexture(scratchBuffer.GetAddress(), &bd->fontTexture, &view, &region,
//                                        nvn::CopyFlags::NONE);
//        nvn::CommandHandle handle = bd->cmdBuf->EndRecording();
//        bd->queue->SubmitCommands(1, &handle);

        nvn::SamplerBuilder samplerBuilder{};
        samplerBuilder.SetDefaults()
                .SetDevice(bd->device)
                .SetMinMagFilter(nvn::MinFilter::LINEAR, nvn::MagFilter::LINEAR)
                .SetWrapMode(nvn::WrapMode::CLAMP_TO_EDGE, nvn::WrapMode::CLAMP_TO_EDGE, nvn::WrapMode::CLAMP_TO_EDGE);

        if (!bd->fontSampler.Initialize(&samplerBuilder)) {
            Logger::log("Failed to Init Font Sampler!\n");
            return false;
        }

        bd->textureId = 512;
        bd->samplerId = 512;

        // we only need to register 1 texture, so id doesn't particularly matter (so long as source game does not have more than 511 textures loaded)
        bd->texPool->RegisterTexture(bd->textureId, &bd->fontTexture, &view);

        bd->samplerPool->RegisterSampler(bd->samplerId, &bd->fontSampler);

        bd->fontTexHandle = bd->device->GetTextureHandle(bd->textureId, bd->samplerId);
        io.Fonts->SetTexID(&bd->fontTexHandle);

        scratchBuffer.Finalize();
        scratchMemPool.Finalize();
        IM_FREE(scratchPool);

        Logger::log("Finished.\n");

        return true;
    }

    bool setupShaders(u8 *shaderBinary, ulong binarySize) {

        Logger::log("Setting up ImGui Shaders.\n");

        auto bd = getBackendData();

        if (!bd->shaderProgram.Initialize(bd->device)) {
            Logger::log("Failed to Initialize Shader Program!");
            return false;
        }

        bd->shaderMemory = IM_NEW(MemoryBuffer)(binarySize, shaderBinary, nvn::MemoryPoolFlags::CPU_UNCACHED |
                                                                          nvn::MemoryPoolFlags::GPU_CACHED |
                                                                          nvn::MemoryPoolFlags::SHADER_CODE);

        if (!bd->shaderMemory->IsBufferReady()) {
            Logger::log("Shader Memory Pool not Ready! Unable to continue.\n");
            return false;
        }

        BinaryHeader offsetData = BinaryHeader((u32 *) shaderBinary);

        nvn::BufferAddress addr = bd->shaderMemory->GetBufferAddress();

        nvn::ShaderData &vertShaderData = bd->shaderDatas[0];
        vertShaderData.data = addr + offsetData.mVertexDataOffset;
        vertShaderData.control = shaderBinary + offsetData.mVertexControlOffset;

        nvn::ShaderData &fragShaderData = bd->shaderDatas[1];
        fragShaderData.data = addr + offsetData.mFragmentDataOffset;
        fragShaderData.control = shaderBinary + offsetData.mFragmentControlOffset;

        if (!bd->shaderProgram.SetShaders(2, bd->shaderDatas)) {
            Logger::log("Failed to Set shader data for program.\n");
            return false;
        }

        bd->shaderProgram.SetDebugLabel("ImGuiShader");

        // Uniform Block Object Memory Setup

        bd->uniformMemory = IM_NEW(MemoryBuffer)(UBOSIZE);

        if (!bd->uniformMemory->IsBufferReady()) {
            Logger::log("Uniform Memory Pool not Ready! Unable to continue.\n");
            return false;
        }

        // setup vertex attrib & stream

        bd->attribStates[0].SetDefaults().SetFormat(nvn::Format::RG32F, offsetof(ImDrawVert, pos)); // pos
        bd->attribStates[1].SetDefaults().SetFormat(nvn::Format::RG32F, offsetof(ImDrawVert, uv)); // uv
        bd->attribStates[2].SetDefaults().SetFormat(nvn::Format::RGBA8_UI2F, offsetof(ImDrawVert, col)); // color

        bd->streamState.SetDefaults().SetStride(sizeof(ImDrawVert));

        Logger::log("Finished.\n");

        return true;
    }

    void InitBackend(const NvnBackendInitInfo &initInfo) {
        ImGuiIO &io = ImGui::GetIO();
        EXL_ASSERT(!io.BackendRendererUserData, "Already Initialized Imgui Backend!");

        io.BackendPlatformName = "Switch";
        io.BackendRendererName = "imgui_impl_nvn";
        io.IniFilename = nullptr;
        io.MouseDrawCursor = false;
        io.ConfigFlags |= ImGuiConfigFlags_IsTouchScreen;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.BackendFlags |= ImGuiBackendFlags_HasGamepad;
        io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;

        auto *bd = IM_NEW(NvnBackendData)();
        io.BackendRendererUserData = (void *) bd;

        bd->device = initInfo.device;
        bd->queue = initInfo.queue;
        bd->cmdBuf = initInfo.cmdBuf;
        bd->texPool = initInfo.texPool;
        bd->samplerPool = initInfo.samplerPool;
        bd->isInitialized = false;

        nvn::DebugCallbackFunc callbackFunc = [](nvn::DebugCallbackSource::Enum source,
                                                 nvn::DebugCallbackType::Enum type, int unkInt,
                                                 nvn::DebugCallbackSeverity::Enum severity, const char *unkStr,
                                                 void *unkPtr) {
            Logger::log("Str Val: %s\n", unkStr);
        };

        bd->device->InstallDebugCallback(callbackFunc, nullptr, true);

        if (createShaders()) {
            Logger::log("Shader Binaries Loaded! Setting up Render Data.\n");

            if (bd->isUseTestShader)
                initTestShader();

            if (setupShaders(bd->imguiShaderBinary.ptr, bd->imguiShaderBinary.size) && setupFont()) {
                Logger::log("Rendering Setup!\n");

                bd->isInitialized = true;

            } else {
                Logger::log("Failed to Setup Render Data!\n");
            }
        }
    }

    void ShutdownBackend() {

    }

    void updateInput() {
        ImGuiIO &io = ImGui::GetIO();

        constexpr int mapping[][2] = {
                {ImGuiKey_GamepadFaceDown,    static_cast<const int>(nn::hid::NpadButton::A)},
                {ImGuiKey_GamepadFaceRight,   static_cast<const int>(nn::hid::NpadButton::B)},
                {ImGuiKey_GamepadFaceUp,      static_cast<const int>(nn::hid::NpadButton::X)},
                {ImGuiKey_GamepadFaceLeft,    static_cast<const int>(nn::hid::NpadButton::Y)},
                {ImGuiKey_GamepadL1,          static_cast<const int>(nn::hid::NpadButton::L)},
                {ImGuiKey_GamepadR1,          static_cast<const int>(nn::hid::NpadButton::R)},
                {ImGuiKey_GamepadL2,          static_cast<const int>(nn::hid::NpadButton::ZL)},
                {ImGuiKey_GamepadR2,          static_cast<const int>(nn::hid::NpadButton::ZR)},
                {ImGuiKey_GamepadStart,       static_cast<const int>(nn::hid::NpadButton::Plus)},
                {ImGuiKey_GamepadBack,        static_cast<const int>(nn::hid::NpadButton::Minus)},
                {ImGuiKey_GamepadDpadLeft,    static_cast<const int>(nn::hid::NpadButton::Left)},
                {ImGuiKey_GamepadDpadRight,   static_cast<const int>(nn::hid::NpadButton::Right)},
                {ImGuiKey_GamepadDpadUp,      static_cast<const int>(nn::hid::NpadButton::Up)},
                {ImGuiKey_GamepadDpadDown,    static_cast<const int>(nn::hid::NpadButton::Down)},
                {ImGuiKey_GamepadLStickLeft,  static_cast<const int>(nn::hid::NpadButton::StickLLeft)},
                {ImGuiKey_GamepadLStickRight, static_cast<const int>(nn::hid::NpadButton::StickLRight)},
                {ImGuiKey_GamepadLStickUp,    static_cast<const int>(nn::hid::NpadButton::StickLUp)},
                {ImGuiKey_GamepadLStickDown,  static_cast<const int>(nn::hid::NpadButton::StickLDown)},
        };

        for (auto [im_k, nx_k]: mapping) {
            if (InputHelper::isButtonDown((nn::hid::NpadButton) nx_k))
                io.AddKeyEvent((ImGuiKey) im_k, true);
            else if (InputHelper::isButtonUp((nn::hid::NpadButton) nx_k))
                io.AddKeyEvent((ImGuiKey) im_k, false);
        }
    }

    void newFrame() {
        ImGuiIO &io = ImGui::GetIO();
        auto *bd = getBackendData();

        io.DisplaySize = ImVec2(DISPWIDTH, DISPHEIGHT);
        u64 curTick = nn::os::GetSystemTick();
        io.DeltaTime = (((bd->lastTick - curTick) * 625) / 12) / 1e9;
        bd->lastTick = nn::os::GetSystemTick();
    }

    void renderDrawData(ImDrawData *drawData) {

        if (!drawData->Valid) {
//            Logger::log("Draw Data was Invalid! Skipping Render.");
            return;
        }

        if (drawData->CmdListsCount == 0) {
//            Logger::log("Command List was Empty! Skipping Render.\n");
            return;
        }

        auto bd = getBackendData();
        ImGuiIO &io = ImGui::GetIO();

        if (!bd->isInitialized) {
            Logger::log("Backend Data was not fully initialized!\n");
            return;
        }

        if (bd->isUseTestShader) {
            renderTestShader();
            return;
        }

        bd->cmdBuf->BeginRecording();

//        float defColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};
//        bd->cmdBuf->ClearColor(0, defColor, nvn::ClearColorMask::RGBA);
//        bd->cmdBuf->ClearDepthStencil(1.0f, true, 0, 0xFF);

        bd->cmdBuf->BindProgram(&bd->shaderProgram, nvn::ShaderStageBits::VERTEX | nvn::ShaderStageBits::FRAGMENT);

        bd->cmdBuf->BindUniformBuffer(nvn::ShaderStage::VERTEX, 0, *bd->uniformMemory, UBOSIZE);
        bd->cmdBuf->UpdateUniformBuffer(*bd->uniformMemory, UBOSIZE, 0, sizeof(projMatrix), &projMatrix);

        bd->cmdBuf->BindVertexAttribState(3, bd->attribStates);
        bd->cmdBuf->BindVertexStreamState(1, &bd->streamState);

        nvn::PolygonState polyState;
        polyState.SetDefaults();
        polyState.SetPolygonMode(nvn::PolygonMode::FILL);
        polyState.SetCullFace(nvn::Face::NONE);
        polyState.SetFrontFace(nvn::FrontFace::CCW);
        bd->cmdBuf->BindPolygonState(&polyState);

        nvn::ColorState colorState;
        colorState.SetDefaults();
        colorState.SetLogicOp(nvn::LogicOp::COPY);
        colorState.SetAlphaTest(nvn::AlphaFunc::ALWAYS);
        for (int i = 0; i < 8; ++i) {
            colorState.SetBlendEnable(i, true);
        }
        bd->cmdBuf->BindColorState(&colorState);

        nvn::BlendState blendState;
        blendState.SetDefaults();
        blendState.SetBlendFunc(nvn::BlendFunc::SRC_ALPHA, nvn::BlendFunc::ONE_MINUS_SRC_ALPHA, nvn::BlendFunc::ONE,
                                nvn::BlendFunc::ONE_MINUS_SRC_ALPHA);
        blendState.SetBlendEquation(nvn::BlendEquation::ADD, nvn::BlendEquation::ADD);
        bd->cmdBuf->BindBlendState(&blendState);

        nvn::ChannelMaskState colorMask;
        colorMask.SetDefaults();
        bd->cmdBuf->BindChannelMaskState(&colorMask);

        nvn::DepthStencilState depthState;
        depthState.SetDefaults();
        depthState.SetDepthTestEnable(false);
        depthState.SetStencilTestEnable(false);
        bd->cmdBuf->BindDepthStencilState(&depthState);

        size_t totalVtxSize = drawData->TotalVtxCount * sizeof(ImDrawVert);
        if (!bd->vtxBuffer || bd->vtxBuffer->GetPoolSize() < totalVtxSize) {
            if (bd->vtxBuffer) {
                bd->vtxBuffer->Finalize();
                IM_FREE(bd->vtxBuffer);
                Logger::log("Resizing Vertex Buffer to Size: %d\n", totalVtxSize);
            } else {
                Logger::log("Initializing Vertex Buffer to Size: %d\n", totalVtxSize);
            }

            bd->vtxBuffer = IM_NEW(MemoryBuffer)(totalVtxSize);
        }

        size_t totalIdxSize = drawData->TotalIdxCount * sizeof(ImDrawIdx);
        if (!bd->idxBuffer || bd->idxBuffer->GetPoolSize() < totalIdxSize) {
            if (bd->idxBuffer) {

                bd->idxBuffer->Finalize();
                IM_FREE(bd->idxBuffer);

                Logger::log("Resizing Index Buffer to Size: %d\n", totalIdxSize);
            } else {
                Logger::log("Initializing Index Buffer to Size: %d\n", totalIdxSize);
            }

            bd->idxBuffer = IM_NEW(MemoryBuffer)(totalIdxSize);

        }

        if (!(bd->vtxBuffer->IsBufferReady() && bd->idxBuffer->IsBufferReady())) {
            Logger::log("Cannot Draw Data! Buffers are not Ready.\n");
            return;
        }

        // bind vtx buffer
        bd->cmdBuf->BindVertexBuffer(0, (*bd->vtxBuffer), bd->vtxBuffer->GetPoolSize());

        size_t vtxOffset = 0, idxOffset = 0;

        // load data into buffers
        for (size_t i = 0; i < drawData->CmdListsCount; i++) {

            auto cmdList = drawData->CmdLists[i];

            size_t vtxSize = cmdList->VtxBuffer.Size * sizeof(ImDrawVert);
            size_t idxSize = cmdList->IdxBuffer.Size * sizeof(ImDrawIdx);

            memcpy(bd->vtxBuffer->GetMemPtr() + vtxOffset, cmdList->VtxBuffer.Data, vtxSize);
            memcpy(bd->idxBuffer->GetMemPtr() + idxOffset, cmdList->IdxBuffer.Data, idxSize);

            vtxOffset += vtxSize;
            idxOffset += idxSize;
        }

        nvn::TextureHandle boundTextureHandle = 0;
        // process commands
        for (int i = 0; i < drawData->CmdListsCount; ++i) {

            if (drawData->CmdListsCount == 0)
                continue;

            auto cmdList = drawData->CmdLists[i];

            for (auto cmd: cmdList->CmdBuffer) {
//                ImVec2 clip_min(cmd.ClipRect.x, cmd.ClipRect.y);
//                ImVec2 clip_max(cmd.ClipRect.z, cmd.ClipRect.w);
//                if (clip_max.x <= clip_min.x || clip_max.y <= clip_min.y)
//                    continue;
//
//                bd->cmdBuf->SetScissor((int) clip_min.x, (int) (drawData->DisplaySize.y - clip_max.y),
//                                       (int) (clip_max.x - clip_min.x), (int) (clip_max.y - clip_min.y));

                nvn::TextureHandle TexID = *(nvn::TextureHandle *) cmd.TextureId;

                if (boundTextureHandle != TexID) {
                    boundTextureHandle = TexID;
                    bd->cmdBuf->BindTexture(nvn::ShaderStage::FRAGMENT, 0, TexID);
                }

                bd->cmdBuf->DrawElementsBaseVertex(nvn::DrawPrimitive::TRIANGLES,
                                                   nvn::IndexType::UNSIGNED_SHORT, cmd.ElemCount,
                                                   (*bd->idxBuffer) + (cmd.IdxOffset * sizeof(ImDrawIdx)),
                                                   cmd.VtxOffset);

//                bd->cmdBuf->DrawElements(nvn::DrawPrimitive::TRIANGLES, nvn::IndexType::UNSIGNED_SHORT,
//                                         cmd.ElemCount * 3, (*bd->idxBuffer) + (cmd.IdxOffset * sizeof(ImDrawIdx)));

            }
        }

        // bd->cmdBuf->DrawElements(nvn::DrawPrimitive::TRIANGLES, nvn::IndexType::UNSIGNED_SHORT, drawData->TotalVtxCount / 3, *bd->idxBuffer);

        // bd->cmdBuf->Barrier(nvn::BarrierBits::ORDER_FRAGMENTS);

        auto handle = bd->cmdBuf->EndRecording();
        bd->queue->SubmitCommands(1, &handle);
    }

}
