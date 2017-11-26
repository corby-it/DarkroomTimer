#pragma once

#include <Button.h>
#include "defs.h"

enum class BtnId : uint8_t {
    Left = PIN_BTN_LEFT,
    Right = PIN_BTN_RIGHT,
    Up = PIN_BTN_UP,
    Down = PIN_BTN_DOWN,
    Start = PIN_BTN_START,
    Focus = PIN_BTN_FOCUS,
    Mode = PIN_BTN_MODE,
    None = 255,
};

extern Button Left;
extern Button Right;
extern Button btnUp;
extern Button btnDown;
extern Button btnStart;
extern Button btnFocus;
extern Button btnMode;


BtnId getInput();
String getInputName(BtnId id);