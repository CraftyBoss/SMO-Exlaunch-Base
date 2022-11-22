#pragma once
/**
 * @file PlayerActorBase.h
 * @brief base class for PlayerActor
 * Vtable loc: 1D77980
 */

#include <math/seadMatrix.h>
#include "PlayerHackKeeper.h"
#include "al/LiveActor/LiveActor.h"
#include "game/Interfaces/IUsePlayerHack.h"
#include "game/Player/PlayerInitInfo.h"
#include "game/Player/IUsePlayerPuppet.h"

class PlayerActorBase : public al::LiveActor, public IUsePlayerHack {
public:
    PlayerActorBase(const char*);
    virtual void init(const al::ActorInitInfo&) override;
    virtual void movement(void) override;
    virtual void initPlayer(const al::ActorInitInfo&, const PlayerInitInfo&);
    virtual int getPortNo() const;
    virtual void getViewMtx() const;
    virtual IUsePlayerCollision* getPlayerCollision() const;
    PlayerHackKeeper* getPlayerHackKeeper() const override;
    virtual bool isEnableDemo();
    virtual void startDemo();
    virtual void endDemo();
    virtual void startDemoPuppetable();
    virtual void endDemoPuppetable();
    virtual void startDemoShineGet();
    virtual void endDemoShineGet();
    virtual void startDemoMainShineGet();
    virtual void endDemoMainShineGet();
    virtual void startDemoHack();
    virtual void endDemoHack();
    virtual void startDemoKeepBind();
    virtual void noticeDemoKeepBindExecute();
    virtual void endDemoKeepBind();
    virtual void startDemoKeepCarry();
    virtual void endDemoKeepCarry();
    virtual void getDemoActor();
    virtual void getDemoAnimator();
    virtual bool isDamageStopDemo() const;
    virtual IUsePlayerPuppet* getPlayerPuppet();
    virtual void* getPlayerInfo() const;
    virtual bool checkDeathArea();
    virtual void sendCollisionMsg();
    virtual bool receivePushMsg(const al::SensorMsg*, al::HitSensor*, al::HitSensor*, float);
private:
    sead::Matrix34f* mViewMtx;
    int mPort;
};

namespace rs {
    void initPlayerActorInfo(PlayerActorBase*, const PlayerInitInfo&);
}