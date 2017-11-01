#include "timer_functions.h"
#include "globals.h"


// ------------------------------------
// STATE "SplashScreen"
// ------------------------------------
void SplashScreenState::enter() {
    lcd.setCursor(1, 0);
    lcd.print(F("Enlarger Timer"));
    lcd.setCursor(6, 1);
    lcd.print(VERSION);
}

void SplashScreenState::loop() {
    if (getInput() != BtnId::None)
        fsm.transitionTo(stSetTime);
}

void SplashScreenState::exit() {
    lcd.clear();
}


// ------------------------------------
// STATE "SetTime"
// ------------------------------------

void SetTimeState::enter() {
    DBG("stSetTimeEnter");
    DBG(getDigitName(currDigit));

    // init lcd
    lcd.clear();
    lcd.print(F("Set Time:"));
    lcd.setCursor(lcdTimeCursorPos, 1);
    lcd.print(currTime.str());
    updateLcd();
    lcd.blink();
}

void SetTimeState::loop() {
    auto input = getInput();
    
    switch (input) {
    case BtnId::Left:
        currDigit = currDigit == 3 ? 3 : currDigit + 1;
        DBG(getDigitName(currDigit));
        break;
    case BtnId::Right:
        currDigit = currDigit == 0 ? 0 : currDigit - 1;
        DBG(getDigitName(currDigit));
        break;
    case BtnId::Up:
        currTime += currTime.getDigit(currDigit) == 9 ? 0 : getMult(currDigit);
        DBG(currTime.str());
        break;
    case BtnId::Down:
        currTime -= currTime.getDigit(currDigit) == 0 ? 0 : getMult(currDigit);
        DBG(currTime.str());
        break;
    case BtnId::Focus:
        stFocus.returnState = this;
        fsm.transitionTo(stFocus);
        break;
    case BtnId::StartStop:
        stRunning.returnState = this;
        stRunning.exposureTime =    currTime;
        fsm.transitionTo(stRunning);
        break;
    case BtnId::Mode:
        fsm.transitionTo(stSetFstop);
        break;
    }

    if(input != BtnId::None)
        updateLcd();
}

void SetTimeState::updateLcd() {
    lcd.setCursor(lcdTimeCursorPos, 1);
    lcd.print(currTime.str());

    switch (currDigit) {
    case DIG_TENTH: lcd.setCursor(lcdTimeCursorPos + 4, 1); break;
    case DIG_ONE: lcd.setCursor(lcdTimeCursorPos + 2, 1); break;
    case DIG_TEN: lcd.setCursor(lcdTimeCursorPos + 1, 1); break;
    case DIG_HUNDRED: lcd.setCursor(lcdTimeCursorPos, 1); break;
    default: break;
    }
}

void SetTimeState::exit() {
    DBG("stSetTimeExit");
    lcd.noBlink();
}

// ------------------------------------
// STATE "SetFstop"
// ------------------------------------

void SetFstopState::enter() {
    DBG("stSetFstopEnter");

    // to avoid a -INF number of stops
    if (stSetTime.currTime == 0)
        stSetTime.currTime++;

    DBG(String(stSetTime.currTime.stops()) + " (" + stSetTime.currTime.str() + ")");

    lcd.clear();
    lcd.print(F("Set Stop:"));
    lcd.setCursor(6, 1);
    lcd.print(F("->"));
    updateLcd();
}

void SetFstopState::loop() {
    auto input = getInput();
    switch (input) {
    case BtnId::Left:
        currFstop--;
        DBG(currFstop.name());
        break;
    case BtnId::Right:
        currFstop++;
        DBG(currFstop.name());
        break;
    case BtnId::Up: {
        stSetTime.currTime += currFstop;
        DBG(String(stSetTime.currTime.stops()) + " (" + stSetTime.currTime.str() + ")");
        break;
    }
    case BtnId::Down: {
        stSetTime.currTime -= currFstop;
        DBG(String(stSetTime.currTime.stops()) + " (" + stSetTime.currTime.str() + ")");
        break;
    }
    case BtnId::Focus:
        stFocus.returnState = this;
        fsm.transitionTo(stFocus);
        break;
    case BtnId::StartStop:
        stRunning.returnState = this;
        stRunning.exposureTime = stSetTime.currTime;
        fsm.transitionTo(stRunning);
        break;
    case BtnId::Mode:
        fsm.transitionTo(stTestStripStop);
        break;
    }

    if (input != BtnId::None)
        updateLcd();
}

void SetFstopState::updateLcd()
{
    lcd.setCursor(lcdStepCursorPos, 0);
    lcd.print(currFstop.name());
    lcd.setCursor(lcdStopCursorPos, 1);
    lcd.print(stSetTime.currTime.stopsStr());
    lcd.setCursor(lcdTimeCursorPos, 1);
    lcd.print(stSetTime.currTime.str());
}

void SetFstopState::exit() {
    DBG("stSetFstopExit");
}


// ------------------------------------
// STATE "Running"
// ------------------------------------

void RunningState::enter() {
    if (exposureTime != 0) {
        digitalWrite(PIN_LED, HIGH);

        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print(F("Running!"));
        lcd.setCursor(lcdTimeCursorPos, 1);
        lcd.print(Time().str() + F(" -> ") + exposureTime.str());
    }

    dispatcher.subscribe(*this);

    DBG("stRunningEnter");
}

void RunningState::loop() {
    if (getInput() == BtnId::StartStop)
        fsm.transitionTo(*returnState);
}

void RunningState::updateLcd() {
    lcd.setCursor(lcdTimeCursorPos, 1);
    lcd.print(timerCounter.str());
}

void RunningState::timerEvent() {
    if (timerCounter < exposureTime) {
        timerCounter++;
        updateLcd();
        DBG(String("Running: ") + timerCounter.str() + "/" + exposureTime.str());
    }
    else {
        fsm.transitionTo(*returnState);
    }
}

void RunningState::exit() {
    digitalWrite(PIN_LED, LOW);

    dispatcher.unsubscribe(*this);
    timerCounter = 0;
    DBG("stRunningExit");
}


// ------------------------------------
// STATE "Focus"
// ------------------------------------

void FocusState::enter() {
    DBG("stFocusEnter");
    digitalWrite(PIN_LED, HIGH);

    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print(F("Focusing..."));
}

void FocusState::loop() {
    if (getInput() == BtnId::Focus)
        fsm.transitionTo(*returnState);
}

void FocusState::exit() {
    DBG("stFocusExit");
    digitalWrite(PIN_LED, LOW);
}
