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

        enum class NpadButton : u64 {
            A = 1LL << 0,
            B = 1LL << 1,
            X = 1LL << 2,
            Y = 1LL << 3,
            StickL = 1LL << 4,
            StickR = 1LL << 5,
            L = 1LL << 6,
            R = 1LL << 7,
            ZL = 1LL << 8,
            ZR = 1LL << 9,
            Plus = 1LL << 10,
            Minus = 1LL << 11,
            Left = 1LL << 12,
            Up = 1LL << 13,
            Right = 1LL << 14,
            Down = 1LL << 15,
            StickLLeft = 1LL << 16,
            StickLUp = 1LL << 17,
            StickLRight = 1LL << 18,
            StickLDown = 1LL << 19,
            StickRLeft = 1LL << 20,
            StickRUp = 1LL << 21,
            StickRRight = 1LL << 22,
            StickRDown = 1LL << 23,
            LeftSL = 1LL << 24,
            LeftSR = 1LL << 25,
            RightSL = 1LL << 26,
            RightSR = 1LL << 27,
            Palma = 1LL << 28,
            Verification = 1LL << 29,
            HandheldLeftB = 1LL << 30, // (Left B button on NES controllers in Handheld mode)
            LeftC = 1LL << 31, // [12.0.0+] (Left C button in N64 controller)
            UpC = 1LL << 32, // [12.0.0+] (Up C button in N64 controller)
            RightC = 1LL << 33, // [12.0.0+] (Right C button in N64 controller)
            DownC = 1LL << 34, // [12.0.0+] (Down C button in N64 controller)
        };

        enum class NpadAttribute {
            IsConnected = 1 << 0,
            IsWired = 1 << 1,
            IsLeftConnected = 1 << 2,
            IsLeftWired = 1 << 3,
            IsRightConnected = 1 << 4,
            IsRightWired = 1 << 5,
        };

        enum class NpadStyleTag {
            NpadStyleFullKey = 1 << 0,         // (Pro Controller)
            NpadStyleHandheld = 1 << 1,         // (Joy-Con controller in handheld mode)
            NpadStyleJoyDual = 1 << 2,         // (Joy-Con controller in dual mode)
            NpadStyleJoyLeft = 1 << 3,         // (Joy-Con left controller in single mode)
            NpadStyleJoyRight = 1 << 4,         // (Joy-Con right controller in single mode)
            NpadStyleGc = 1 << 5,             // (GameCube controller)
            NpadStylePalma = 1 << 6,         // (Poké Ball Plus controller)
            NpadStyleLark = 1 << 7,             // (NES/Famicom controller)
            NpadStyleHandheldLark = 1 << 8,     // (NES/Famicom controller in handheld mode)
            NpadStyleLucia = 1 << 9,         // (SNES controller)
            NpadStyleLagon = 1 << 10,         // [12.0.0+] (N64 controller)
            NpadStyleLager = 1 << 11,         // [13.0.0+] (Sega Genesis controller)
            // bits 12-28 Reserved
            NpadStyleSystemExt = 1 << 29,     // (generic external controller)
            NpadStyleSystem = 1 << 30,         // (generic controller)
            // bit 31 Reserved
        };

        enum class NpadSystemProperties : u64 {
            IsChargingJoyDual = 1LL << 0,
            IsChargingJoyLeft = 1LL << 1,
            IsChargingJoyRight = 1LL << 2,
            IsPoweredJoyDual = 1LL << 3,
            IsPoweredJoyLeft = 1LL << 4,
            IsPoweredJoyRight = 1LL << 5,
            IsUnsuportedButtonPressedOnNpadSystem = 1LL << 9,
            IsUnsuportedButtonPressedOnNpadSystemExt = 1LL << 10,
            IsAbxyButtonOriented = 1LL << 11,
            IsSlSrButtonOriented = 1LL << 12,
            IsPlusAvailable = 1LL << 13, // [4.0.0+]
            IsMinusAvailable = 1LL << 14, // [4.0.0+]
            IsDirectionalButtonsAvailable = 1LL << 15, // [8.0.0+]
        };

        enum class TouchAttribute {
            Transferable = 1 << 0,
            IsConnected = 1 << 1
        };

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

        typedef nn::util::BitFlagSet<64, NpadButton> NpadButtonSet;
        typedef nn::util::BitFlagSet<32, nn::hid::NpadStyleTag> NpadStyleSet;
        typedef nn::util::BitFlagSet<32, NpadAttribute> NpadAttributeSet;
        typedef nn::util::BitFlagSet<32, MouseButton> MouseButtonSet;
        typedef nn::util::BitFlagSet<32, MouseAttribute> MouseAttributeSet;
        typedef nn::util::BitFlagSet<32, TouchAttribute> TouchAttributeSet;

        struct AnalogStickState {
            s32 X;
            s32 Y;
        };

        struct TouchState {
            u64 mDeltaTime;
            TouchAttributeSet mAttributes;
            s32 mFingerId;
            s32 X;
            s32 Y;
            s32 mDiameterX;
            s32 mDiameterY;
            s32 mRotationAngle;
            s32 mReserved;
        };

        struct NpadBaseState {
            u64 mSamplingNumber;
            NpadButtonSet mButtons;
            AnalogStickState mAnalogStickL;
            AnalogStickState mAnalogStickR;
            NpadAttributeSet mAttributes;
            char reserved[4];
        };

        struct NpadFullKeyState : NpadBaseState {
        };
        struct NpadHandheldState : NpadBaseState {
        };
        struct NpadJoyDualState : NpadBaseState {
        };
        struct NpadJoyLeftState : NpadBaseState {
        };
        struct NpadJoyRightState : NpadBaseState {
        };
        struct NpadPalmaState : NpadBaseState {
        };
        struct NpadSystemState : NpadBaseState {
        };
        struct NpadSystemExtState : NpadBaseState {
        };

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

        struct MouseState {
            u64 samplingNumber;
            s32 x;
            s32 y;
            s32 deltaX;
            s32 deltaY;
            s32 wheelDeltaX;
            s32 wheelDeltaY;
            MouseButtonSet buttons;
            MouseAttributeSet attributes;
        };

        void InitializeNpad();

        void SetSupportedNpadIdType(uint const *, ulong);

        void SetSupportedNpadStyleSet(nn::util::BitFlagSet<32, nn::hid::NpadStyleTag>);

        nn::hid::NpadStyleSet GetNpadStyleSet(uint const &port);

        void GetNpadState(nn::hid::NpadFullKeyState *, uint const &port);

        void GetNpadState(nn::hid::NpadHandheldState *, uint const &port);

        void GetNpadState(nn::hid::NpadJoyDualState *, uint const &port);

        void GetNpadState(nn::hid::NpadJoyLeftState *, uint const &port);

        void GetNpadState(nn::hid::NpadJoyRightState *, uint const &port);

        void GetNpadStates(nn::hid::NpadFullKeyState *, int, uint const &port);

        void GetNpadStates(nn::hid::NpadHandheldState *, int, uint const &port);

        void GetNpadStates(nn::hid::NpadJoyDualState *, int, uint const &port);

        void GetNpadStates(nn::hid::NpadJoyLeftState *, int, uint const &port);

        void GetNpadStates(nn::hid::NpadJoyRightState *, int, uint const &port);

        int ShowControllerSupport(nn::hid::ControllerSupportResultInfo *,
                                  ControllerSupportArg const &);

        void InitializeMouse();

        void GetMouseState(nn::hid::MouseState *);

        void InitializeKeyboard();
    }  // namespace hid
}  // namespace nn