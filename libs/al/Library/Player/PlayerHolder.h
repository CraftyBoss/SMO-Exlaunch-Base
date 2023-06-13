#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>

namespace al {
class LiveActor;
class PadRumbleKeeper;

class PlayerHolder {
private:
    struct Player {
        al::LiveActor* mActor = nullptr;
        al::PadRumbleKeeper* mPadRumbleKeeper = nullptr;
    };

    Player* mPlayers = nullptr;
    s32 mBufferSize = 0;
    s32 mPlayerNum = 0;

public:
    PlayerHolder(s32 maxPlayers);
    void clear();
    void registerPlayer(al::LiveActor* actor, al::PadRumbleKeeper* rumbleKeeper);
    al::LiveActor* getPlayer(s32 index) const;
    al::LiveActor* tryGetPlayer(s32 index) const;
    s32 getPlayerNum() const;
    s32 getBufferSize() const;
    bool isFull() const;
    bool isExistPadRumbleKeeper(s32 index) const;
    al::PadRumbleKeeper* getPadRumbleKeeper(s32 index) const;
};

int getPlayerNumMax(al::LiveActor const*);
int getPlayerNumMax(al::PlayerHolder const*);
int getAlivePlayerNum(al::LiveActor const*);
int getAlivePlayerNum(al::PlayerHolder const*);
al::LiveActor* getPlayerActor(al::LiveActor const*,int);
al::LiveActor* getPlayerActor(al::PlayerHolder const*,int);
sead::Vector3f& getPlayerPos(al::LiveActor const*,int);
sead::Vector3f& getPlayerPos(al::PlayerHolder const*,int);
al::LiveActor* tryGetPlayerActor(al::LiveActor const*,int);
al::LiveActor* tryGetPlayerActor(al::PlayerHolder const*,int);
bool isPlayerDead(al::LiveActor const*,int);
bool isPlayerDead(al::PlayerHolder const*,int);
bool isPlayerAreaTarget(al::LiveActor const*,int);
bool isPlayerAreaTarget(al::PlayerHolder const*,int);
al::LiveActor* tryFindAlivePlayerActorFirst(al::LiveActor const*);
al::LiveActor* tryFindAlivePlayerActorFirst(al::PlayerHolder const*);
al::LiveActor* findAlivePlayerActorFirst(al::LiveActor const*);
al::LiveActor* findAlivePlayerActorFirst(al::PlayerHolder const*);
al::PadRumbleKeeper* getPlayerPadRumbleKeeper(al::LiveActor const*,int);
int getPlayerPort(al::PlayerHolder const*,int);
int getPlayerPort(al::LiveActor const*,int);
al::LiveActor* findAlivePlayerActorFromPort(al::PlayerHolder const*,int);
al::LiveActor* tryFindAlivePlayerActorFromPort(al::PlayerHolder const*,int);
al::LiveActor* findAlivePlayerActorFromPort(al::LiveActor const*,int);
al::LiveActor* tryFindAlivePlayerActorFromPort(al::LiveActor const*,int);
int findNearestPlayerId(al::LiveActor const*,float);

}  // namespace al
