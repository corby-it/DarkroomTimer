#pragma once

#include <Button.h>

#define PIN_LED			12
#define PIN_BTN_LEFT	6
#define PIN_BTN_RIGHT	3
#define PIN_BTN_UP		4
#define PIN_BTN_DOWN	5
#define PIN_BTN_START	2
#define PIN_BTN_FOCUS   A0
#define NONE		    255

enum class BtnId : uint8_t {
    Left = PIN_BTN_LEFT,
    Right = PIN_BTN_RIGHT,
    Up = PIN_BTN_UP,
    Down = PIN_BTN_DOWN,
    StartStop = PIN_BTN_START,
    Focus = PIN_BTN_FOCUS,
    None = 255,
};

extern Button btnChange;
extern Button btnUp;
extern Button btnDown;
extern Button btnStart;
extern Button btnFocus;


BtnId getInput();
String getInputName(BtnId id);