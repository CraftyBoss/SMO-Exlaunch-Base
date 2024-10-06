#include "lib.hpp"
#include "imgui_backend/imgui_impl_nvn.hpp"
#include "patches.hpp"
#include "logger/Logger.hpp"
#include "helpers/PlayerHelper.h"
#include "imgui_nvn.h"
#include "ExceptionHandler.h"

#include <basis/seadRawPrint.h>

#include <game/StageScene/StageScene.h>
#include <game/System/GameSystem.h>
#include <game/System/Application.h>
#include <game/HakoniwaSequence/HakoniwaSequence.h>

#include "rs/util.hpp"
#include "file_redirection.h"

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

    if (ImGui::CollapsingHeader("World List")) {
        for (auto &entry: gameSeq->mGameDataHolder.mData->mWorldList->mWorldList) {
            if (ImGui::TreeNode(entry.mMainStageName)) {

                if (isInGame) {
                    if (ImGui::Button("Warp to World")) {
                        PlayerHelper::warpPlayer(entry.mMainStageName, gameSeq->mGameDataHolder);
                    }
                }

                ImGui::BulletText("Clear Main Scenario: %d", entry.mClearMainScenario);
                ImGui::BulletText("Ending Scenario: %d", entry.mEndingScenario);
                ImGui::BulletText("Moon Rock Scenario: %d", entry.mMoonRockScenario);

                if (ImGui::TreeNode("Main Quest Infos")) {
                    for (int i = 0; i < entry.mQuestInfoCount; ++i) {
                        ImGui::BulletText("Quest %d Scenario: %d", i, entry.mMainQuestIndexes[i]);
                    }
                    ImGui::TreePop();
                }

                if (ImGui::CollapsingHeader("Database Entries")) {
                    for (auto &dbEntry: entry.mStageNames) {
                        if (ImGui::TreeNode(dbEntry.mStageName.cstr())) {
                            ImGui::BulletText("Stage Category: %s", dbEntry.mStageCategory.cstr());
                            ImGui::BulletText("Stage Use Scenario: %d", dbEntry.mUseScenario);

                            if (isInGame) {
                                ImGui::Bullet();
                                if (ImGui::SmallButton("Warp to Stage")) {
                                    PlayerHelper::warpPlayer(dbEntry.mStageName.cstr(),
                                                             gameSeq->mGameDataHolder);
                                }
                            }

                            ImGui::TreePop();
                        }
                    }
                }

                ImGui::TreePop();
            }
        }
    }

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

HOOK_DEFINE_TRAMPOLINE(ControlHook) {
    static void Callback(StageScene *scene) {
        Orig(scene);
    }
};

HOOK_DEFINE_REPLACE(ReplaceSeadPrint) {
    static void Callback(const char *format, ...) {
        va_list args;
        va_start(args, format);
        Logger::log(format, args);
        va_end(args);
    }
};


HOOK_DEFINE_TRAMPOLINE(GameSystemInit) {
    static void Callback(GameSystem *thisPtr) {
        Orig(thisPtr);
    }
};

extern "C" void exl_main(void *x0, void *x1) {
    /* Setup hooking enviroment. */
    exl::hook::Initialize();

    nn::os::SetUserExceptionHandler(exception_handler, nullptr, 0, nullptr);
    installExceptionStub();

    Logger::instance().init(LOGGER_IP, 3080);

    runCodePatches();

    GameSystemInit::InstallAtOffset(0x535850);

    // SD File Redirection

    FileRedirection::InstallHooks();

    // Sead Debugging Overriding

    ReplaceSeadPrint::InstallAtOffset(0xB59E28);

    // General Hooks

    ControlHook::InstallAtSymbol("_ZN10StageScene7controlEv");
    PlayerHelper::installHooks();

    // ImGui Hooks
#if IMGUI_ENABLED
    nvnImGui::InstallHooks();

    nvnImGui::addDrawFunc(drawDebugWindow);
    nvnImGui::addDrawFunc(drawFpsWindow);
#endif

}

extern "C" NORETURN void exl_exception_entry() {
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}