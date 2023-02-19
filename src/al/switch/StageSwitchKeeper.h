#pragma once

#include "al/actor/IUseName.h"
#include "al/actor/Placement.h"

namespace al {
    class StageSwitchKeeper;

    class StageSwitchDirector;

    class StageSwitchAccesser;

    class IUseStageSwitch : virtual public al::IUseName {
    public:
        virtual al::StageSwitchKeeper *getStageSwitchKeeper() const = 0;

        virtual void initStageSwitchKeeper() = 0;
    };

    class StageSwitchKeeper {
    public:
        StageSwitchKeeper();

        void init(al::StageSwitchDirector *, al::PlacementInfo const &);

        void tryGetStageSwitchAccesser(char const *);

        StageSwitchAccesser *mStageSwitchAccesser = nullptr; // 0x0
        int mLinkCount = 0; // 0x8
        const char *mSwitchName = nullptr; // 0x10
    };
};