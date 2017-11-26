#include "timer_functions.h"
#include "globals.h"
#include "buzzer.h"


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
        break;
    case BtnId::Right:
        currDigit = currDigit == 0 ? 0 : currDigit - 1;
        break;
    case BtnId::Up:
        currTime += currTime.getDigit(currDigit) == 9 ? 0 : getMult(currDigit);
        break;
    case BtnId::Down:
        currTime -= currTime.getDigit(currDigit) == 0 ? 0 : getMult(currDigit);
        break;
    case BtnId::Focus:
        stFocus.returnState = this;
        fsm.transitionTo(stFocus);
        break;
    case BtnId::Start:
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
    lcd.noBlink();
}

// ------------------------------------
// STATE "SetFstop"
// ------------------------------------

void SetFstopState::enter() {
    // to avoid a -INF number of stops
    if (stSetTime.currTime == 0)
        stSetTime.currTime++;

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
        break;
    case BtnId::Right:
        currFstop++;
        break;
    case BtnId::Up: {
        stSetTime.currTime += currFstop;
        break;
    }
    case BtnId::Down: {
        stSetTime.currTime -= currFstop;
        break;
    }
    case BtnId::Focus:
        stFocus.returnState = this;
        fsm.transitionTo(stFocus);
        break;
    case BtnId::Start:
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

}


// ------------------------------------
// STATE "Running"
// ------------------------------------

void RunningState::enter() {
    if (exposureTime != 0) {
        digitalWrite(PIN_LED, LAMP_ON);

        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print(F("Running!"));
        lcd.setCursor(lcdTimeCursorPos, 1);
        lcd.print(Time().str() + F(" -> ") + exposureTime.str());

        playOnTone();
    }

    dispatcher.subscribe(*this);
}

void RunningState::loop() {
    if (getInput() == BtnId::Start)
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
    }
    else {
        fsm.transitionTo(*returnState);
    }
}

void RunningState::exit() {
    digitalWrite(PIN_LED, LAMP_OFF);

    dispatcher.unsubscribe(*this);

    if (exposureTime != 0)
        playOffTone();

    timerCounter = 0;
}


// ------------------------------------
// STATE "Focus"
// ------------------------------------

void FocusState::enter() {
    digitalWrite(PIN_LED, LAMP_ON);

    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print(F("Focusing..."));
}

void FocusState::loop() {
    if (getInput() == BtnId::Focus)
        fsm.transitionTo(*returnState);
}

void FocusState::exit() {
    digitalWrite(PIN_LED, LAMP_OFF);
}
