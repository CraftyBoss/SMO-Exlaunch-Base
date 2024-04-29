#include "PlayerHelper.h"
#include "lib.hpp"

#include <al/Library/LiveActor/ActorMovementFunction.h>
#include <al/Library/Player/PlayerHolder.h>

#include <al/Library/Memory/HeapUtil.h>
#include <game/GameData/GameDataFunction.h>
#include <logger/Logger.hpp>

namespace PlayerHelper {

    bool isDestroyWorldResource = false;

    void killPlayer(al::LiveActor *actor) {
        PlayerActorHakoniwa *mainPlayer = (PlayerActorHakoniwa *) al::getPlayerActor(actor, 0);

        GameDataFunction::killPlayer(GameDataHolderAccessor(actor));
        mainPlayer->startDemoPuppetable();
        al::setVelocityZero(mainPlayer);
        mainPlayer->mPlayerAnimator->endSubAnim();
        mainPlayer->mPlayerAnimator->startAnimDead();
    }

    void killPlayer(PlayerActorHakoniwa *mainPlayer) {
        GameDataFunction::killPlayer(GameDataHolderAccessor(mainPlayer));
        mainPlayer->startDemoPuppetable();
        al::setVelocityZero(mainPlayer);
        mainPlayer->mPlayerAnimator->endSubAnim();
        mainPlayer->mPlayerAnimator->startAnimDead();
    }

    void warpPlayer(const char *stageName, GameDataHolderAccessor holder, int curScenario) {
        ChangeStageInfo info(holder.mData, "", stageName, false,
                             curScenario,
                             ChangeStageInfo::SubScenarioType::UNK);
        GameDataFunction::tryChangeNextStage(holder, &info);
    }

    void warpPlayer(const char *stageName, HakoniwaSequence *seq, bool isDestroyResource, int curScenario) {
        Logger::log("Requesting Destroy World Resource.\n");
        isDestroyWorldResource = isDestroyResource;
        warpPlayer(stageName, seq->mGameDataHolder, curScenario);
    }

    HOOK_DEFINE_TRAMPOLINE(HakoniwaSequenceDestroyHook) {
        static void Callback(HakoniwaSequence *thisPtr) {
            if (isDestroyWorldResource) {
                if (al::isFirstStep(thisPtr)) {
                    Logger::log("Attempting to reset World Resources.\n");
                    thisPtr->mResourceLoader->tryDestroyWorldResource();
                    al::createWorldResourceHeap(true);
                    thisPtr->mResourceLoader->mWorldResourceHeap = al::getWorldResourceHeap();
                }
                isDestroyWorldResource = false;
            }
            Orig(thisPtr);
        }
    };

    void installHooks() {
        HakoniwaSequenceDestroyHook::InstallAtSymbol("_ZN16HakoniwaSequence10exeDestroyEv");
    }
}