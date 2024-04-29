#pragma once

#include <game/Player/PlayerActorHakoniwa.h>
#include <game/GameData/GameDataHolderAccessor.h>
#include <game/HakoniwaSequence/HakoniwaSequence.h>

namespace PlayerHelper {
    void killPlayer(al::LiveActor *actor);

    void killPlayer(PlayerActorHakoniwa *mainPlayer);

    void warpPlayer(const char *stageName, GameDataHolderAccessor holder, int curScenario = -1);

    void warpPlayer(const char *stageName, HakoniwaSequence *seq, bool isDestroyResource = false, int curScenario = -1);

    void installHooks();

};
