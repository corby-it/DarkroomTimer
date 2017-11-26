#include "btns.h"

Button btnLeft = Button(PIN_BTN_LEFT, PULLUP);
Button btnRight = Button(PIN_BTN_RIGHT, PULLUP);
Button btnUp = Button(PIN_BTN_UP, PULLUP);
Button btnDown = Button(PIN_BTN_DOWN, PULLUP);
Button btnStart = Button(PIN_BTN_START, PULLUP);
Button btnFocus = Button(PIN_BTN_FOCUS, PULLUP);
Button btnMode = Button(PIN_BTN_MODE, PULLUP);

static const uint32_t debounceInterval = 200;  // milliseconds

static uint32_t btnLeftLastPress = 0;
static uint32_t btnRightLastPress = 0;
static uint32_t btnUpLastPress = 0;
static uint32_t btnDownLastPress = 0;
static uint32_t btnStartLastPress = 0;
static uint32_t btnFocusLastPress = 0;
static uint32_t btnModeLastPress = 0;

BtnId getInputReal() {

    if (btnLeft.uniquePress()) {
        if (millis() - btnLeftLastPress >= debounceInterval) {
            btnLeftLastPress = millis();
            return BtnId::Left;
        }
        else return BtnId::None;
    }
    else if (btnRight.uniquePress()) {
        if (millis() - btnRightLastPress >= debounceInterval) {
            btnRightLastPress = millis();
            return BtnId::Right;
        }
        else return BtnId::None;
    }
    else if (btnUp.uniquePress()) {
        if (millis() - btnUpLastPress >= debounceInterval) {
            btnUpLastPress = millis();
            return BtnId::Up;
        }
        else return BtnId::None;
    }
    else if (btnDown.uniquePress()) {
        if (millis() - btnDownLastPress >= debounceInterval) {
            btnDownLastPress = millis();
            return BtnId::Down;
        }
        else return BtnId::None;
    }
    else if (btnStart.uniquePress()) {
        if (millis() - btnStartLastPress >= debounceInterval) {
            btnStartLastPress = millis();
            return BtnId::Start;
        }
        else return BtnId::None;
    }
    else if (btnMode.uniquePress()) {
        if (millis() - btnModeLastPress >= debounceInterval) {
            btnModeLastPress = millis();
            return BtnId::Mode;
        }
        else return BtnId::None;
    }
    else if (btnFocus.uniquePress()) {
        if (millis() - btnFocusLastPress >= debounceInterval) {
            btnFocusLastPress = millis();
            return BtnId::Focus;
        }
        else return BtnId::None;
    }
    else {
        return BtnId::None;
    }
}

BtnId getInput() {
    auto res = getInputReal();
    if (res != BtnId::None) {
        DBG(String("") + millis() + " " + getInputName(res));
    }
    return res;
}

String getInputName(BtnId id)
{
    switch (id) {
    case BtnId::Left: return "btn_left";
    case BtnId::Right: return "btn_right";
    case BtnId::Up: return "btn_up";
    case BtnId::Down: return "btn_down";
    case BtnId::Start: return "btn_start";
    case BtnId::Focus: return "btn_focus";
    case BtnId::Mode: return "btn_mode";
    case BtnId::None: return "none";
    }
}