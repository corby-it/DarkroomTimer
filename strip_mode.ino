#include "strip_mode.h"
#include "globals.h"
#include "fstop.h"
#include <math.h>

static uint32_t currBaseTime = 0;
static fstop fStep = Third;

// ------------------------------------
// STATE "TestStrip"
// ------------------------------------
void TestStripState::enter() {
    DBG("stTestStripEnter");

    stTestStripReady.reset();
    stTestStripRunning.reset();

    lcd.clear();
    lcd.print(F("Test Strip Mode:"));
    lcd.setCursor(0, 1);
    lcd.print(F("<-Mode | Start->"));
}

void TestStripState::loop() {
    switch (getInput()) {
    case BtnId::Mode:
        fsm.transitionTo(stSetTime);
        break;
    case BtnId::StartStop:
        fsm.transitionTo(stTestStripSelectTime);
        break;
    case BtnId::Focus:
        stFocus.returnState = this;
        fsm.transitionTo(stFocus);
    default: break;
    }
}

void TestStripState::exit() {
    DBG("stTestStripExit");
}


// ------------------------------------
// STATE "TestStripSelectTimeStop"
// ------------------------------------
void TestStripSelectTimeState::enter() {
    DBG("stTestStripSelectTimeStopEnter");

    lcd.clear();
    lcd.print(F("Time   ||   Step"));
    lcd.setCursor(7, 1);
    lcd.print(F("||"));
    updateLcd();
    lcd.blink();
}

void TestStripSelectTimeState::loop() {
    auto input = getInput();

    switch (input) {
    case BtnId::Left:
        currCursorPos = currCursorPos == 0 ? 0 : currCursorPos - 1;
        break;
    case BtnId::Right:
        currCursorPos = currCursorPos == 4 ? 4 : currCursorPos + 1;
        break;
    case BtnId::Up:
        if (currCursorPos != 4)
            currBaseTime += getDigit(currBaseTime, 3 - currCursorPos) != 9 ? getMult(3 - currCursorPos) : 0;
        else
            currStep = currStep == Three ? Three : fstop(currStep + 1);
        break;
    case BtnId::Down:
        if (currCursorPos != 4)
            currBaseTime -= getDigit(currBaseTime, 3 - currCursorPos) != 0 ? getMult(3 - currCursorPos) : 0;
        else
            currStep = currStep == Third ? Third : fstop(currStep - 1);
        break;
    case BtnId::Focus:
        stFocus.returnState = this;
        fsm.transitionTo(stFocus);
        break;
    case BtnId::StartStop:
        stTestStripReady.setData(currBaseTime, currStep);
        fsm.transitionTo(stTestStripReady);
        break;
    case BtnId::Mode:
        fsm.transitionTo(stTestStrip);
        break;
    default:
        break;
    }

    if (input != BtnId::None)
        updateLcd();
}

void TestStripSelectTimeState::updateLcd() {
    lcd.setCursor(lcdTimeCursorPos, 1);
    lcd.print(t2slcd(currBaseTime));
    lcd.setCursor(lcdStepCursorPos, 1);
    lcd.print(getFstopNameLcdStrip(currStep));

    switch (currCursorPos) {
    case 0: lcd.setCursor(Hundred, 1); break;
    case 1: lcd.setCursor(Ten, 1); break;
    case 2: lcd.setCursor(One, 1); break;
    case 3: lcd.setCursor(Tenth, 1); break;
    case 4: lcd.setCursor(Step, 1); break;
    default: break;
    }
}

void TestStripSelectTimeState::exit() {
    DBG("stTestStripSelectTimeStopExit");

    lcd.noBlink();
}


// ------------------------------------
// STATE "TestStripReady"
// ------------------------------------
void TestStripReadyState::enter() {
    DBG("stTestStripReadyEnter");
    
    lcd.clear();
    lcd.print(F("Strip: "));
    
    if (exposureCounter == 0)
        lcd.print(F("Base"));
    else
        lcd.print(String(F("# ")) + exposureCounter);
    
    lcd.setCursor(0, 1);
    lcd.print(t2slcd(currTime) + F(" / ") + t2slcd(totalTime));
}

void TestStripReadyState::loop() {
    switch (getInput()) {
    case BtnId::StartStop:
        stTestStripRunning.exposureTime = currTime;
        fsm.transitionTo(stTestStripRunning);
        break;
    case BtnId::Mode:
        fsm.transitionTo(stTestStrip);
        break;
    case BtnId::Focus:
        stFocus.returnState = this;
        fsm.transitionTo(stFocus);
        break;
    default: break;
    }
}

void TestStripReadyState::exit() {
    DBG("stTestStripReadyExit");
}

void TestStripReadyState::setData(uint32_t time, fstop step) {
    currTime = totalTime = time;
    incStep = step;
};

void TestStripReadyState::exposureDone() {
    uint32_t newTotalTime = round(totalTime * getFstopMult(incStep, false));
    newTotalTime = newTotalTime > MAX_TIMER_TIME ? MAX_TIMER_TIME : newTotalTime;

    currTime = newTotalTime - totalTime;
    totalTime = newTotalTime;

    exposureCounter++;
}


// ------------------------------------
// STATE "TestStripRunning"
// ------------------------------------
void TestStripRunningState::enter() {
    if (exposureTime != 0) {
        digitalWrite(PIN_LED, HIGH);

        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print(F("Running!"));
        lcd.setCursor(lcdTimeCursorPos, 1);
        lcd.print(t2slcd(0) + F(" -> ") + t2slcd(exposureTime));
    }

    dispatcher.subscribe(*this);

    DBG("stTestStripRunningEnter");
}

void TestStripRunningState::loop() {
    if (getInput() == BtnId::StartStop)
        fsm.transitionTo(stTestStripReady);
}

void TestStripRunningState::updateLcd() {
    lcd.setCursor(lcdTimeCursorPos, 1);
    lcd.print(t2slcd(timerCounter));
}

void TestStripRunningState::timerEvent() {
    if (timerCounter < exposureTime) {
        timerCounter++;
        updateLcd();
        DBG(String("Running: ") + t2s(timerCounter) + "/" + t2s(exposureTime));
    }
    else {
        fsm.transitionTo(stTestStripReady);
    }
}

void TestStripRunningState::exit() {
    digitalWrite(PIN_LED, LOW);

    dispatcher.unsubscribe(*this);
    stTestStripReady.exposureDone();

    reset();
}