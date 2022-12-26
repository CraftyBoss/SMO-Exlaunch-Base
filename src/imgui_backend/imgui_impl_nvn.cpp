#include "imgui_impl_nvn.hpp"
#include "lib.hpp"
#include "helpers.h"
#include "logger/Logger.hpp"

#include "nn/os.h"
#include "nn/hid.h"

#include "helpers/InputHelper.h"
#include "MemoryPoolMaker.h"

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

    int texIDSelector() {
        {

            static int curId = 256;
            static int downCounter = 0;
            static int upCounter = 0;

            if (InputHelper::isButtonDown(nn::hid::NpadButton::Left)) {
                curId--;
                Logger::log("ID: %d\n", curId);
            } else if (InputHelper::isButtonPressed(nn::hid::NpadButton::Left)) {

                downCounter++;
                if (downCounter > 30) {
                    curId--;
                    Logger::log("ID: %d\n", curId);
                }
            } else {
                downCounter = 0;
            }

            if (InputHelper::isButtonDown(nn::hid::NpadButton::Right)) {
                curId++;
                Logger::log("ID: %d\n", curId);
            } else if (InputHelper::isButtonPressed(nn::hid::NpadButton::Right)) {

                upCounter++;
                if (upCounter > 30) {
                    curId++;
                    Logger::log("ID: %d\n", curId);
                }
            } else {
                upCounter = 0;
            }

            /* fun values with bd->device->GetTextureHandle(curId, 256):
             * 282 = Window Texture
             * 393 = Some sort of render pass (shadow?) nvm it just seems to be the first occurrence of many more textures like it
             * 257 = debug font texture
             */

            return curId;
        }
    }

    void renderTestShader() {

        auto bd = getBackendData();

        int pointCount = 6;

        size_t totalVtxSize = pointCount * sizeof(ImDrawVert);
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

        ImDrawVert *verts = (ImDrawVert *) bd->vtxBuffer->GetMemPtr();

        float scale = 3.0f;

        float imageX = bd->fontTexture.GetWidth(); // 100 * scale;
        float imageY = bd->fontTexture.GetHeight();  // 100 * scale;

        float minXVal = (DISPWIDTH / 2) - (imageX); // 300
        float maxXVal = (DISPWIDTH / 2) + (imageX); // 300
        float minYVal = (DISPHEIGHT / 2) - (imageY); // 400
        float maxYVal = (DISPHEIGHT / 2) + (imageY); // 400

        ImU32 quadColor = IM_COL32_WHITE;

        // top left
        ImDrawVert p1 = {
                .pos = ImVec2(minXVal, minYVal),
                .uv = ImVec2(0.0f, 0.0f),
                .col = quadColor
        };
        // top right
        ImDrawVert p2 = {
                .pos = ImVec2(minXVal, maxYVal),
                .uv = ImVec2(0.0f, 1.0f),
                .col = quadColor
        };
        // bottom left
        ImDrawVert p3 = {
                .pos = ImVec2(maxXVal, minYVal),
                .uv = ImVec2(1.0f, 0.0f),
                .col = quadColor
        };
        // bottom right
        ImDrawVert p4 = {
                .pos = ImVec2(maxXVal, maxYVal),

                .uv = ImVec2(1.0f, 1.0f),
                .col = quadColor
        };

        verts[0] = p4;
        verts[1] = p2;
        verts[2] = p1;

        verts[3] = p1;
        verts[4] = p3;
        verts[5] = p4;

        bd->cmdBuf->BeginRecording();
        bd->cmdBuf->BindProgram(&bd->shaderProgram, nvn::ShaderStageBits::VERTEX | nvn::ShaderStageBits::FRAGMENT);

        bd->cmdBuf->BindUniformBuffer(nvn::ShaderStage::VERTEX, 0, *bd->uniformMemory, UBOSIZE);
        bd->cmdBuf->UpdateUniformBuffer(*bd->uniformMemory, UBOSIZE, 0, sizeof(projMatrix), &projMatrix);

        nvn::VertexAttribState attributes[3];
        attributes[0].SetDefaults().SetFormat(nvn::Format::RG32F, offsetof(ImDrawVert, pos));
        attributes[1].SetDefaults().SetFormat(nvn::Format::RG32F, offsetof(ImDrawVert, uv));
        attributes[2].SetDefaults().SetFormat(nvn::Format::RGBA8, offsetof(ImDrawVert, col));

        nvn::VertexStreamState stream;
        stream.SetDefaults();
        stream.SetStride(sizeof(ImDrawVert));

        bd->cmdBuf->BindVertexAttribState(3, attributes);
        bd->cmdBuf->BindVertexStreamState(1, &stream);

        bd->cmdBuf->BindVertexBuffer(0, (*bd->vtxBuffer), bd->vtxBuffer->GetPoolSize());

        bd->cmdBuf->SetTexturePool(&bd->texPool);
        bd->cmdBuf->SetSamplerPool(&bd->samplerPool);

        static bool isDisableGameRender = true;

        if (bd->isDisableInput && InputHelper::isButtonDown(nn::hid::NpadButton::L)) {
            isDisableGameRender = !isDisableGameRender;
        }

        if (isDisableGameRender) {
            float defColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};
            bd->cmdBuf->ClearColor(0, defColor, nvn::ClearColorMask::RGBA);
            bd->cmdBuf->ClearDepthStencil(1.0f, true, 0, 0xFF);
        }

        setRenderStates();

        bd->cmdBuf->BindTexture(nvn::ShaderStage::FRAGMENT, 0, bd->fontTexHandle);

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

        // init sampler and texture pools

        int sampDescSize = 0;
        bd->device->GetInteger(nvn::DeviceInfo::SAMPLER_DESCRIPTOR_SIZE, &sampDescSize);
        int texDescSize = 0;
        bd->device->GetInteger(nvn::DeviceInfo::TEXTURE_DESCRIPTOR_SIZE, &texDescSize);

        int sampMemPoolSize = sampDescSize * MaxSampDescriptors;
        int texMemPoolSize = texDescSize * MaxTexDescriptors;
        int totalPoolSize = ALIGN_UP(sampMemPoolSize + texMemPoolSize, 0x1000);
        if (!MemoryPoolMaker::createPool(&bd->sampTexMemPool, totalPoolSize)) {
            Logger::log("Failed to Create Texture/Sampler Memory Pool!\n");
            return false;
        }

        if (!bd->samplerPool.Initialize(&bd->sampTexMemPool, 0, MaxSampDescriptors)) {
            Logger::log("Failed to Create Sampler Pool!\n");
            return false;
        }

        if (!bd->texPool.Initialize(&bd->sampTexMemPool, sampMemPoolSize, MaxTexDescriptors)) {
            Logger::log("Failed to Create Texture Pool!\n");
            return false;
        }

        // convert imgui font texels

        unsigned char *pixels;
        int width, height, pixelByteSize;
        io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height, &pixelByteSize);
        int texPoolSize = pixelByteSize * width * height;

        if (!MemoryPoolMaker::createPool(&bd->fontMemPool, ALIGN_UP(texPoolSize, 0x1000),
                                         nvn::MemoryPoolFlags::CPU_UNCACHED | nvn::MemoryPoolFlags::GPU_CACHED)) {
            Logger::log("Failed to Create Font Memory Pool!\n");
            return false;
        }

        bd->texBuilder.SetDefaults()
                .SetDevice(bd->device)
                .SetTarget(nvn::TextureTarget::TARGET_2D)
                .SetFormat(nvn::Format::RGBA8)
                .SetSize2D(width, height)
                .SetStorage(&bd->fontMemPool, 0);

        if (!bd->fontTexture.Initialize(&bd->texBuilder)) {
            Logger::log("Failed to Create Font Texture!\n");
            return false;
        }

        // setup font texture

        nvn::CopyRegion region = {
                .xoffset = 0,
                .yoffset = 0,
                .zoffset = 0,
                .width = bd->fontTexture.GetWidth(),
                .height = bd->fontTexture.GetHeight(),
                .depth = 1
        };

        bd->fontTexture.WriteTexels(nullptr, &region, pixels);
        bd->fontTexture.FlushTexels(nullptr, &region);

        bd->samplerBuilder.SetDefaults()
                .SetDevice(bd->device)
                .SetMinMagFilter(nvn::MinFilter::LINEAR, nvn::MagFilter::LINEAR)
                .SetWrapMode(nvn::WrapMode::CLAMP, nvn::WrapMode::CLAMP, nvn::WrapMode::CLAMP);

        if (!bd->fontSampler.Initialize(&bd->samplerBuilder)) {
            Logger::log("Failed to Init Font Sampler!\n");
            return false;
        }

        bd->textureId = 257;
        bd->samplerId = 257;

        // we only need to register 1 texture, so id doesn't particularly matter (so long as source game does not have more than 511 textures loaded)
        bd->texPool.RegisterTexture(bd->textureId, &bd->fontTexture, nullptr);
        bd->samplerPool.RegisterSampler(bd->samplerId, &bd->fontSampler);
        bd->fontTexHandle = bd->device->GetTextureHandle(bd->textureId, bd->samplerId);
        io.Fonts->SetTexID(&bd->fontTexHandle);

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
        bd->attribStates[2].SetDefaults().SetFormat(nvn::Format::RGBA8, offsetof(ImDrawVert, col)); // color

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
        bd->isInitialized = false;

        io.Fonts->AddFontDefault();

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

    void setRenderStates() {

        auto bd = getBackendData();

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
                                nvn::BlendFunc::ZERO);
        blendState.SetBlendEquation(nvn::BlendEquation::ADD, nvn::BlendEquation::ADD);
        bd->cmdBuf->BindBlendState(&blendState);
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

        bd->cmdBuf->BindProgram(&bd->shaderProgram, nvn::ShaderStageBits::VERTEX | nvn::ShaderStageBits::FRAGMENT);

        bd->cmdBuf->BindUniformBuffer(nvn::ShaderStage::VERTEX, 0, *bd->uniformMemory, UBOSIZE);
        bd->cmdBuf->UpdateUniformBuffer(*bd->uniformMemory, UBOSIZE, 0, sizeof(projMatrix), &projMatrix);

        bd->cmdBuf->BindVertexAttribState(3, bd->attribStates);
        bd->cmdBuf->BindVertexStreamState(1, &bd->streamState);

        bd->cmdBuf->SetTexturePool(&bd->texPool);
        bd->cmdBuf->SetSamplerPool(&bd->samplerPool);

        setRenderStates();

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

            }
        }

        auto handle = bd->cmdBuf->EndRecording();
        bd->queue->SubmitCommands(1, &handle);
    }

}