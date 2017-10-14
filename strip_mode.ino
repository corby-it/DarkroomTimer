#include "strip_mode.h"
#include "globals.h"
#include "fstop.h"

static uint32_t baseTime = 0;
static fstop fStep = Third;

// ------------------------------------
// STATE "TestStrip"
// ------------------------------------
void TestStripState::enter() {
    DBG("stTestStripEnter");

    lcd.clear();
    lcd.print("StripMode:");
}

void TestStripState::loop() {
    switch (getInput()) {
    case BtnId::Mode:
        fsm.transitionTo(stSetTime);
        break;
    case BtnId::StartStop:
        fsm.transitionTo(stTestStripSelectTime);
        break;
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
}

void TestStripSelectTimeState::loop() {

}

void TestStripSelectTimeState::exit() {
    DBG("stTestStripSelectTimeStopExit");
}


// ------------------------------------
// STATE "TestStripReady"
// ------------------------------------
void TestStripReadyState::enter() {
    DBG("stTestStripReadyEnter");
}

void TestStripReadyState::loop() {

}

void TestStripReadyState::exit() {
    DBG("stTestStripReadyExit");
}


// ------------------------------------
// STATE "TestStripRunning"
// ------------------------------------
void TestStripRunningState::enter() {
    DBG("stTestStripRunningEnter");
}

void TestStripRunningState::loop() {

}

void TestStripRunningState::exit() {
    DBG("stTestStripRunningExit");
}

