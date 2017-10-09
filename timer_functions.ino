#include "timer_functions.h"
#include "globals.h"

// ------------------------------------
// STATE "SetTime"
// ------------------------------------

void stSetTimeEnter() {
    DBG("stSetTimeEnter");
    returnState = &stSetTime;
    DBG(getDigitName(currDigit));
}

void stSetTimeLoop() {
    switch (getInput()) {
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
        fsm.transitionTo(stFocus);
        break;
    case BtnId::StartStop:
        fsm.transitionTo(stRunning);
        break;
    case BtnId::Mode:
        fsm.transitionTo(stSetFstop);
        break;
    }
}

void stSetTimeExit() {
    DBG("stSetTimeExit");
}

// ------------------------------------
// STATE "SetFstop"
// ------------------------------------

void stSetFstopEnter() {
    DBG("stSetFstopEnter");
    returnState = &stSetFstop;

    // to avoid a -INF number of stops
    if (currTime == 0)
        ++currTime;

    DBG(String(t2f(currTime)) + " (" + t2s(currTime) + ")");
}

void stSetFstopLoop() {
    switch (getInput()) {
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
        fsm.transitionTo(stFocus);
        break;
    case BtnId::StartStop:
        fsm.transitionTo(stRunning);
        break;
    case BtnId::Mode:
        fsm.transitionTo(stTestStrip);
        break;
    }
}

void stSetFstopExit() {
    DBG("stSetFstopExit");
}


// ------------------------------------
// STATE "Running"
// ------------------------------------

void stRunningEnter() {
    if (currTime != 0)
        digitalWrite(PIN_LED, HIGH);
    running = true;
    DBG("stRunningEnter");
}

void stRunningLoop() {
    if (getInput() == BtnId::StartStop)
        fsm.transitionTo(*returnState);
}

void stRunningExit() {
    digitalWrite(PIN_LED, LOW);
    running = false;
    timerCounter = 0;
    DBG("stRunningExit");
}


// ------------------------------------
// STATE "Focus"
// ------------------------------------

void stFocusEnter() {
    DBG("stFocusEnter");
    digitalWrite(PIN_LED, HIGH);
}

void stFocusLoop() {
    if (getInput() == BtnId::Focus)
        fsm.transitionTo(*returnState);
}

void stFocusExit() {
    DBG("stFocusExit");
    digitalWrite(PIN_LED, LOW);
}
