#include "lib.hpp"
#include "imgui_backend/imgui_impl_nvn.hpp"
#include "patches.hpp"
#include "logger/Logger.hpp"
#include "helpers/PlayerHelper.h"
#include "imgui_nvn.h"

#include <basis/seadRawPrint.h>

#include <game/StageScene/StageScene.h>
#include <game/System/GameSystem.h>
#include <game/System/Application.h>
#include <game/HakoniwaSequence/HakoniwaSequence.h>
#include <exception/ExceptionHandler.h>

#include "rs/util.hpp"
#include "file_redirection.h"
#include "stage_warp.h"

#define IMGUI_ENABLED true

void drawDebugWindow() {
    HakoniwaSequence *gameSeq = (HakoniwaSequence *) GameSystemFunction::getGameSystem()->mCurSequence;

    ImGui::Begin("Game Debug Window");
    ImGui::SetWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);

    ImGui::Text("Current Sequence Name: %s", gameSeq->getName().cstr());

    static bool showWindow = false;

    if (ImGui::Button("Toggle Demo Window")) {
        showWindow = !showWindow;
    }

    if (showWindow) {
        ImGui::ShowDemoWindow();
    }

    auto curScene = gameSeq->mStageScene;

    bool isInGame =
            curScene && curScene->mIsAlive;

    if (isInGame) {
        StageScene *stageScene = gameSeq->mStageScene;
        PlayerActorBase *playerBase = rs::getPlayerActor(stageScene);

        if (ImGui::Button("Kill Mario")) {
            PlayerHelper::killPlayer(playerBase);
        }
    }

    ImGui::End();
}

void drawFpsWindow() {
    ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));

    ImGui::Begin("FPSCounter", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize |
                                        ImGuiWindowFlags_NoSavedSettings |
                                        ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBackground);

    ImGui::Text("FPS: %d\n", static_cast<int>(roundf(Application::instance()->mFramework->calcFps())));

    ImGui::End();
}

HOOK_DEFINE_REPLACE(ReplaceSeadPrint) {
    static void Callback(const char *format, ...) {
        va_list args;
        va_start(args, format);
        Logger::log(format, args);
        va_end(args);
    }
};

extern "C" void exl_main(void *x0, void *x1) {
    /* Setup hooking environment. */
    exl::hook::Initialize();

    handler::installExceptionHandler([](handler::ExceptionInfo &info) {
        handler::printCrashReport(info);
        return false;
    });

    Logger::instance().init(LOGGER_IP, 3080);

    runCodePatches();

    // SD File Redirection
    FileRedirection::InstallHooks();

    // Sead Debugging Overriding
    ReplaceSeadPrint::InstallAtOffset(0xB59E28);

    // General Hooks
    PlayerHelper::installHooks();

    // ImGui Hooks
#if IMGUI_ENABLED
    nvnImGui::InstallHooks();

    nvnImGui::addDrawFunc(drawDebugWindow);
    nvnImGui::addDrawFunc(drawFpsWindow);
    nvnImGui::addDrawFunc(drawStageWarpWindow);
#endif
}

extern "C" NORETURN void exl_exception_entry() {
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}