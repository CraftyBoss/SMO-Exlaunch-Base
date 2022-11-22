/**
* @file hid.h
* @brief Functions that help process gamepad inputs.
*/

#pragma once

#include <gfx/seadColor.h>
#include <nx/types.h>
#include <nn/util.h>

namespace nn {
    namespace hid {
        struct NpadHandheldState;
        struct NpadStyleTag;

        struct ControllerSupportArg {
           u8 mMinPlayerCount;
           u8 mMaxPlayerCount;
           u8 mTakeOverConnection;
           bool mLeftJustify;
           bool mPermitJoyconDual;
           bool mSingleMode;
           bool mUseColors;
           sead::Color4u8 mColors[4];
           u8 mUsingControllerNames;
           char mControllerNames[4][0x81];
        };

        struct ControllerSupportResultInfo {
           int mPlayerCount;
           int mSelectedId;
        };

        void InitializeNpad();
        void SetSupportedNpadIdType(u32 const*, u64);
        void SetSupportedNpadStyleSet(nn::util::BitFlagSet<32, nn::hid::NpadStyleTag>);
        void GetNpadStyleSet(u32 const&);
        void GetNpadStates(nn::hid::NpadHandheldState*, s32, u32 const&);
        int ShowControllerSupport(nn::hid::ControllerSupportResultInfo*,
                                        ControllerSupportArg const&);

        enum class MouseButton {
            Left,
            Right,
            Middle,
            Forward,
            Back
        };

        enum class MouseAttribute {
            Transferable,
            IsConnected
        };

        struct MouseState {
            u64 samplingNumber;
            s32 x;
            s32 y;
            s32 deltaX;
            s32 deltaY;
            s32 wheelDeltaX;
            s32 wheelDeltaY;
            nn::util::BitFlagSet<32, MouseButton> buttons;
            nn::util::BitFlagSet<32, MouseAttribute> attributes;
        };
        void InitializeMouse();
        void GetMouseState(nn::hid::MouseState*);
        void InitializeKeyboard();
    }  // namespace hid
}  // namespace nn