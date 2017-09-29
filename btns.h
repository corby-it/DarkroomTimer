#pragma once

#include <Button.h>

#define PIN_LED			8
#define PIN_BTN_LEFT	11
#define PIN_BTN_RIGHT	12
#define PIN_BTN_UP		9
#define PIN_BTN_DOWN	10
#define PIN_BTN_START	A0
#define PIN_BTN_FOCUS   A1
#define PIN_BTN_MODE    A2
#define NONE		    255

enum class BtnId : uint8_t {
    Left = PIN_BTN_LEFT,
    Right = PIN_BTN_RIGHT,
    Up = PIN_BTN_UP,
    Down = PIN_BTN_DOWN,
    StartStop = PIN_BTN_START,
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