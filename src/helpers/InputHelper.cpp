#include "InputHelper.h"

static const char *styleNames[] = {
        "Pro Controller",
        "Joy-Con controller in handheld mode",
        "Joy-Con controller in dual mode",
        "Joy-Con left controller in single mode",
        "Joy-Con right controller in single mode",
        "GameCube controller",
        "Poké Ball Plus controller",
        "NES/Famicom controller",
        "NES/Famicom controller in handheld mode",
        "SNES controller",
        "N64 controller",
        "Sega Genesis controller",
        "generic external controller",
        "generic controller",
};

nn::hid::NpadBaseState InputHelper::prevState{};
nn::hid::NpadBaseState InputHelper::curState{};
ulong InputHelper::selectedPort = -1;

const char *getStyleName(nn::hid::NpadStyleSet style) {

    u32 index = -1;

    if (style.isFlagSet(nn::hid::NpadStyleTag::NpadStyleFullKey)) { index = 0; }
    if (style.isFlagSet(nn::hid::NpadStyleTag::NpadStyleHandheld)) { index = 1; }
    if (style.isFlagSet(nn::hid::NpadStyleTag::NpadStyleJoyDual)) { index = 2; }
    if (style.isFlagSet(nn::hid::NpadStyleTag::NpadStyleJoyLeft)) { index = 3; }
    if (style.isFlagSet(nn::hid::NpadStyleTag::NpadStyleJoyRight)) { index = 4; }
    if (style.isFlagSet(nn::hid::NpadStyleTag::NpadStyleGc)) { index = 5; }
    if (style.isFlagSet(nn::hid::NpadStyleTag::NpadStylePalma)) { index = 6; }
    if (style.isFlagSet(nn::hid::NpadStyleTag::NpadStyleLark)) { index = 7; }
    if (style.isFlagSet(nn::hid::NpadStyleTag::NpadStyleHandheldLark)) { index = 8; }
    if (style.isFlagSet(nn::hid::NpadStyleTag::NpadStyleLucia)) { index = 9; }
    if (style.isFlagSet(nn::hid::NpadStyleTag::NpadStyleLagon)) { index = 10; }
    if (style.isFlagSet(nn::hid::NpadStyleTag::NpadStyleLager)) { index = 11; }
    if (style.isFlagSet(nn::hid::NpadStyleTag::NpadStyleSystemExt)) { index = 12; }
    if (style.isFlagSet(nn::hid::NpadStyleTag::NpadStyleSystem)) { index = 13; }

    if (index != -1) {
        return styleNames[index];
    } else {
        return "Unknown";
    }
}

void InputHelper::updatePadState() {

    prevState = curState;

    tryGetState(&curState, selectedPort);

}

bool InputHelper::tryGetState(nn::hid::NpadBaseState *state, ulong port) {

    nn::hid::NpadStyleSet styleSet = nn::hid::GetNpadStyleSet(port);

    if (styleSet.isFlagSet(nn::hid::NpadStyleTag::NpadStyleFullKey)) {
        nn::hid::GetNpadState((nn::hid::NpadFullKeyState *) state, port);
    } else if (styleSet.isFlagSet(nn::hid::NpadStyleTag::NpadStyleHandheld)) {
        nn::hid::GetNpadState((nn::hid::NpadHandheldState *) state, port);
    } else if (styleSet.isFlagSet(nn::hid::NpadStyleTag::NpadStyleJoyDual)) {
        nn::hid::GetNpadState((nn::hid::NpadJoyDualState *) state, port);
    } else if (styleSet.isFlagSet(nn::hid::NpadStyleTag::NpadStyleJoyLeft)) {
        nn::hid::GetNpadState((nn::hid::NpadJoyLeftState *) state, port);
    } else if (styleSet.isFlagSet(nn::hid::NpadStyleTag::NpadStyleJoyRight)) {
        nn::hid::GetNpadState((nn::hid::NpadJoyRightState *) state, port);
    } else {
        return false;
    }

    return true;

}

bool InputHelper::isButtonPressed(nn::hid::NpadButton button) {
    return curState.mButtons.isFlagSet(button);
}

bool InputHelper::isButtonDown(nn::hid::NpadButton button) {
    return curState.mButtons.isFlagSet(button) && !prevState.mButtons.isFlagSet(button);
}

bool InputHelper::isButtonUp(nn::hid::NpadButton button) {
    return !curState.mButtons.isFlagSet(button) && prevState.mButtons.isFlagSet(button);
}

