#include "timer_functions.h"
#include "globals.h"


// ------------------------------------
// STATE "SetTime"
// ------------------------------------
void SplashScreenState::enter() {
    lcd.setCursor(1, 0);
    lcd.print("Enlarger Timer");
    lcd.setCursor(6, 1);
    lcd.print("v1.0");
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
    lcd.print("SetTime:");
    lcd.setCursor(lcdTimeCursorPos, 1);
    lcd.print(t2slcd(currTime));
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
        currTime += getDigit(currTime, currDigit) != 9 ? getMult(currDigit) : 0;
        DBG(t2s(currTime));
        break;
    case BtnId::Down:
        currTime -= getDigit(currTime, currDigit) != 0 ? getMult(currDigit) : 0;
        DBG(t2s(currTime));
        break;
    case BtnId::Focus:
        stFocus.returnState = this;
        fsm.transitionTo(stFocus);
        break;
    case BtnId::StartStop:
        stRunning.returnState = this;
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
    lcd.print(t2slcd(currTime));

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
    if (currTime == 0)
        ++currTime;

    DBG(String(t2f(currTime)) + " (" + t2s(currTime) + ")");

    lcd.clear();
    lcd.print("SetStop:");
    lcd.setCursor(6, 1);
    lcd.print("->");
    updateLcd();
}

void SetFstopState::loop() {
    auto input = getInput();
    switch (input) {
    case BtnId::Left:
        currFstop = fstop(currFstop == fstop::Base ? fstop::Base : currFstop - 1);
        DBG(getFstopName(currFstop));
        break;
    case BtnId::Right:
        currFstop = fstop(currFstop == fstop::Three ? fstop::Three : currFstop + 1);
        DBG(getFstopName(currFstop));
        break;
    case BtnId::Up: {
        uint32_t newTime = round(currTime * getFstopMult(currFstop, false));
        currTime = newTime > MAX_TIMER_TIME ? MAX_TIMER_TIME : newTime;
        DBG(String(t2f(currTime)) + " (" + t2s(currTime) + ")");
        break;
    }
    case BtnId::Down: {
        int32_t newTime = round(currTime * getFstopMult(currFstop, true));
        currTime = newTime < MIN_TIMER_TIME ? MIN_TIMER_TIME : newTime;
        DBG(String(t2f(currTime)) + " (" + t2s(currTime) + ")");
        break;
    }
    case BtnId::Focus:
        stFocus.returnState = this;
        fsm.transitionTo(stFocus);
        break;
    case BtnId::StartStop:
        stRunning.returnState = this;
        fsm.transitionTo(stRunning);
        break;
    case BtnId::Mode:
        fsm.transitionTo(stTestStrip);
        break;
    }

    if (input != BtnId::None)
        updateLcd();
}

void SetFstopState::updateLcd()
{
    lcd.setCursor(lcdStepCursorPos, 0);
    lcd.print(getFstopNameLcd(currFstop));
    lcd.setCursor(lcdStopCursorPos, 1);
    lcd.print(t2flcd(currTime));
    lcd.setCursor(lcdTimeCursorPos, 1);
    lcd.print(t2slcd(currTime));
}

void SetFstopState::exit() {
    DBG("stSetFstopExit");
}


// ------------------------------------
// STATE "Running"
// ------------------------------------

void RunningState::enter() {
    if (currTime != 0) {
        digitalWrite(PIN_LED, HIGH);

        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("Running!");
        lcd.setCursor(lcdTimeCursorPos, 1);
        lcd.print(t2slcd(0) + " -> " + t2slcd(currTime));
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
    lcd.print(t2slcd(timerCounter));
}

void RunningState::timerEvent() {
    if (timerCounter < currTime) {
        timerCounter++;
        updateLcd();
        DBG(String("Running: ") + t2s(timerCounter) + "/" + t2s(currTime));
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
    lcd.print("Focusing...");
}

void FocusState::loop() {
    if (getInput() == BtnId::Focus)
        fsm.transitionTo(*returnState);
}

void FocusState::exit() {
    DBG("stFocusExit");
    digitalWrite(PIN_LED, LOW);
}
