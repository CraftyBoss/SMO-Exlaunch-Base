#pragma once

#include "nn/hid.h"

class InputHelper {
public:
    static void updatePadState();

    static void setPort(ulong port) { selectedPort = port; }

    static bool isButtonPressed(nn::hid::NpadButton button);

    static bool isButtonDown(nn::hid::NpadButton button);

    static bool isButtonUp(nn::hid::NpadButton button);

private:
    static bool tryGetState(nn::hid::NpadBaseState *state, ulong port);

    static nn::hid::NpadBaseState curState;
    static nn::hid::NpadBaseState prevState;
    static ulong selectedPort;

};