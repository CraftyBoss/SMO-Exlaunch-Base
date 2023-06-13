#pragma once

#include <al/Library/LiveActor/LiveActor.h>

#include <game/Util/ActorDimensionKeeper.h>
#include <game/Info/QuestInfo.h>
#include <game/Interfaces/IUseDimension.h>
#include <game/Info/ShineInfo.h>

#include "types.h"

class Shine : public al::LiveActor , public IUseDimension {
    public:
        Shine(const char* actorName);

        ActorDimensionKeeper *getActorDimensionKeeper() const override;

        void offAppear();
        void onAppear();
        
        void getDirectWithDemo(void);
        void getDirect();
        void get();

        void onSwitchGet(void);
        
        bool isGot() const;

        void setGrandShine(void);

        undefined padding[0x10];
        // 0x11C mIsEmptyShine
        ShineInfo *curShineInfo; // 0x120
        undefined padding_290[0x278 - 0x128];
        QuestInfo *shineQuestInfo; // 0x278
        void *unkPtr1; // 0x280
        ActorDimensionKeeper *mDimensionKeeper; // 0x288
        int shineId; // 0x290
};