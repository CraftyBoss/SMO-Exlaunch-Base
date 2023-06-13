#pragma once

#include <al/Library/LiveActor/LiveActor.h>

namespace al {
void initSubActorKeeper(LiveActor *,ActorInitInfo const&,char const*,int);
void initSubActorKeeperNoFile(LiveActor *,ActorInitInfo const&,int);
void registerSubActor(LiveActor *,LiveActor *);
void registerSubActorSyncClipping(LiveActor *,LiveActor *);
void registerSubActorSyncClippingAndHide(LiveActor *,LiveActor *);
void registerSubActorSyncAll(LiveActor *,LiveActor *);
void setSubActorOffSyncClipping(LiveActor *);
}