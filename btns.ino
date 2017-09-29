#include "btns.h"

Button btnLeft = Button(PIN_BTN_LEFT, PULLUP);
Button btnRight = Button(PIN_BTN_RIGHT, PULLUP);
Button btnUp = Button(PIN_BTN_UP, PULLUP);
Button btnDown = Button(PIN_BTN_DOWN, PULLUP);
Button btnStart = Button(PIN_BTN_START, PULLUP);
Button btnFocus = Button(PIN_BTN_FOCUS, PULLUP);
Button btnMode = Button(PIN_BTN_MODE, PULLUP);


BtnId getInput() {
    if (btnLeft.uniquePress()) return BtnId::Left;
    else if (btnRight.uniquePress()) return BtnId::Right;
    else if (btnUp.uniquePress()) return BtnId::Up;
    else if (btnDown.uniquePress()) return BtnId::Down;
    else if (btnStart.uniquePress()) return BtnId::StartStop;
    else if (btnFocus.uniquePress()) return BtnId::Focus;
    else if (btnMode.uniquePress()) return BtnId::Mode;
    else return BtnId::None;
}

String getInputName(BtnId id)
{
    switch (id) {
    case BtnId::Left: return "btn_left";
    case BtnId::Right: return "btn_right";
    case BtnId::Up: return "btn_up";
    case BtnId::Down: return "btn_down";
    case BtnId::StartStop: return "btn_start";
    case BtnId::Focus: return "btn_focus";
    case BtnId::Mode: return "btn_mode";
    case BtnId::None: return "none";
    }
}