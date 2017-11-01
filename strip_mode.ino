#include "strip_mode.h"
#include "globals.h"
#include "fstop.h"
#include <math.h>


// ------------------------------------
// STATE "TestStripStop"
// ------------------------------------
void TestStripStopState::enter() {
    DBG("stTestStripStopStateExit");

    stTestStripReady.reset();
    stTestStripRunning.reset();

    lcd.clear();
    lcd.print(F("Stop Strip Mode:"));
    lcd.setCursor(0, 1);
    lcd.print(F("<-Mode | Start->"));
}

void TestStripStopState::loop() {
    switch (getInput()) {
    case BtnId::Mode:
        fsm.transitionTo(stTestStripTime);
        break;
    case BtnId::StartStop:
        fsm.transitionTo(stTestStripSelectStop);
        break;
    case BtnId::Focus:
        stFocus.returnState = this;
        fsm.transitionTo(stFocus);
    default: break;
    }
}

void TestStripStopState::exit() {
    DBG("stTestStripStopStateExit");
}

// ------------------------------------
// STATE "TestStripTime"
// ------------------------------------
void TestStripTimeState::enter() {
    DBG("stTestStripTimeStateEnter");

    stTestStripReady.reset();
    stTestStripRunning.reset();

    lcd.clear();
    lcd.print(F("Time Strip Mode:"));
    lcd.setCursor(0, 1);
    lcd.print(F("<-Mode | Start->"));
}

void TestStripTimeState::loop() {
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

void TestStripTimeState::exit() {
    DBG("stTestStripTimeStateExit");
}

// ------------------------------------
// STATE "TestStripSelectStopState"
// ------------------------------------
void TestStripSelectStopState::enter() {
    DBG("stTestStripSelectStopStateEnter");

    lcd.clear();
    lcd.print(F("Time   ||   Step"));
    lcd.setCursor(7, 1);
    lcd.print(F("||"));
    updateLcd();
    lcd.blink();
}

void TestStripSelectStopState::loop() {
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
            currBaseTime += currBaseTime.getDigit(3 - currCursorPos) == 9 ? 0 : getMult(3 - currCursorPos);
        else
            currStep++;
        break;
    case BtnId::Down:
        if (currCursorPos != 4)
            currBaseTime -= currBaseTime.getDigit(3 - currCursorPos) == 0 ? 0 : getMult(3 - currCursorPos);
        else if(currStep != FStop::lowest)
            currStep--;
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
        fsm.transitionTo(stTestStripStop);
        break;
    default:
        break;
    }

    if (input != BtnId::None)
        updateLcd();
}

void TestStripSelectStopState::updateLcd() {
    lcd.setCursor(lcdTimeCursorPos, 1);
    lcd.print(currBaseTime.str());
    lcd.setCursor(lcdStepCursorPos, 1);
    lcd.print(currStep.nameLcdStrip());

    switch (currCursorPos) {
    case 0: lcd.setCursor(Hundred, 1); break;
    case 1: lcd.setCursor(Ten, 1); break;
    case 2: lcd.setCursor(One, 1); break;
    case 3: lcd.setCursor(Tenth, 1); break;
    case 4: lcd.setCursor(Step, 1); break;
    default: break;
    }
}

void TestStripSelectStopState::exit() {
    DBG("stTestStripSelectStopStateExit");

    lcd.noBlink();
}


// ------------------------------------
// STATE "TestStripSelectTimeState"
// ------------------------------------
void TestStripSelectTimeState::enter() {
    DBG("stTestStripSelectTimeStateEnter");

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
        currCursorPos = currCursorPos == 7 ? 7 : currCursorPos + 1;
        break;
    case BtnId::Up:
        if (currCursorPos < 4)
            currBaseTime += currBaseTime.getDigit(3 - currCursorPos) == 9 ? 0 : getMult(3 - currCursorPos);
        else
            currStepTime += currStepTime.getDigit(7 - currCursorPos) == 9 ? 0 : getMult(7 - currCursorPos);
        break;
    case BtnId::Down:
        if (currCursorPos < 4)
            currBaseTime -= currBaseTime.getDigit(3 - currCursorPos) == 0 ? 0 : getMult(3 - currCursorPos);
        else
            currStepTime -= currStepTime.getDigit(7 - currCursorPos) == 0 ? 0 : getMult(7 - currCursorPos);
        break;
    case BtnId::Focus:
        stFocus.returnState = this;
        fsm.transitionTo(stFocus);
        break;
    case BtnId::StartStop:
        stTestStripReady.setData(currBaseTime, currStepTime);
        fsm.transitionTo(stTestStripReady);
        break;
    case BtnId::Mode:
        fsm.transitionTo(stTestStripStop);
        break;
    default:
        break;
    }

    if (input != BtnId::None)
        updateLcd();
}

void TestStripSelectTimeState::updateLcd() {
    lcd.setCursor(lcdTimeCursorPos, 1);
    lcd.print(currBaseTime.str());
    lcd.setCursor(lcdStepCursorPos, 1);
    lcd.print(currStepTime.str());

    switch (currCursorPos) {
    case 0: lcd.setCursor(BaseHundred, 1); break;
    case 1: lcd.setCursor(BaseTen, 1); break;
    case 2: lcd.setCursor(BaseOne, 1); break;
    case 3: lcd.setCursor(BaseTenth, 1); break;
    case 4: lcd.setCursor(StepHundred, 1); break;
    case 5: lcd.setCursor(StepTen, 1); break;
    case 6: lcd.setCursor(StepOne, 1); break;
    case 7: lcd.setCursor(StepTenth, 1); break;
    default: break;
    }
}

void TestStripSelectTimeState::exit() {
    DBG("stTestStripSelectTimeStateExit");

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
    lcd.print(currTime.str() + F(" / ") + totalTime.str());
}

void TestStripReadyState::loop() {
    switch (getInput()) {
    case BtnId::StartStop:
        stTestStripRunning.exposureTime = currTime;
        fsm.transitionTo(stTestStripRunning);
        break;
    case BtnId::Mode:
        fsm.transitionTo(stTestStripStop);
        break;
    default: break;
    }
}

void TestStripReadyState::exit() {
    DBG("stTestStripReadyExit");
}

void TestStripReadyState::setData(Time time, FStop step) {
    currTime = totalTime = time;
    stopStep = step;
    useStop = true;
};

void TestStripReadyState::setData(Time time, Time step) {
    currTime = totalTime = time;
    timeStep = step;
    useStop = false;
};

void TestStripReadyState::exposureDone() {
    Time newTotalTime = useStop ? totalTime + stopStep : totalTime + timeStep;
    
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
        lcd.print(Time().str() + F(" -> ") + exposureTime.str());
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
    lcd.print(timerCounter.str());
}

void TestStripRunningState::timerEvent() {
    if (timerCounter < exposureTime) {
        timerCounter++;
        updateLcd();
        DBG(String("Running: ") + timerCounter.str() + "/" + exposureTime.str());
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