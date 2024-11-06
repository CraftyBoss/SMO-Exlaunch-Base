#pragma once

namespace al {
    class ShadowMaskCtrl;

    class DepthShadowMapCtrl;

    class ShadowKeeper {
    private:
        ShadowMaskCtrl *mShadowMaskCtrl = nullptr;
        DepthShadowMapCtrl *mDepthShadowMapCtrl = nullptr;

    public:
        void initAfterPlacement(al::GraphicsSystemInfo *);

        void update();

        bool isHide() const;

        void hide();

        void show();
    };

    static_assert(sizeof(ShadowKeeper) == 0x10);
}  // namespace al
