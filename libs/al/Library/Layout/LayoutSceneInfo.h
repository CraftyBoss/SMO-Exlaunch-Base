#pragma once

#include <al/Library/Scene/SceneObjHolder.h>
#include <al/Library/Camera/CameraDirector.h>

namespace eui {
    class FontMgr;
}

namespace al {
    class PadRumbleDirector;

    class MessageSystem;

    class GamePadSystem;

    class LayoutSceneInfo {
    private:
        eui::FontMgr *mFontMgr = nullptr;
        al::CameraDirector *mCameraDirector = nullptr;
        al::PadRumbleDirector *mPadRumbleDirector = nullptr;
        al::SceneObjHolder *mSceneObjHolder = nullptr;
        const al::MessageSystem *mMessageSystem = nullptr;
        const al::GamePadSystem *mGamePadSystem = nullptr;

    public:
        LayoutSceneInfo();

        eui::FontMgr *getFontMgr() const { return mFontMgr; }

        al::CameraDirector *getCameraDirector() const { return mCameraDirector; }

        al::PadRumbleDirector *getPadRumbleDirector() const { return mPadRumbleDirector; }

        al::SceneObjHolder *getSceneObjHolder() const { return mSceneObjHolder; }

        const al::MessageSystem *getMessageSystem() const { return mMessageSystem; }

        const al::GamePadSystem *getGamePadSystem() const { return mGamePadSystem; }
    };
}  // namespace al
