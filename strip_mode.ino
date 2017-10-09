#include "strip_mode.h"
#include "globals.h"
#include "fstop.h"

static uint32_t baseTime = 0;
static fstop fStep = Third;

// ------------------------------------
// STATE "TestStrip"
// ------------------------------------
void stTestStripEnter() {
    DBG("stTestStripEnter");
    returnState = &stTestStrip;
}

void stTestStripLoop() {
    switch (getInput()) {
    case BtnId::Mode:
        fsm.transitionTo(stSetTime);
        break;
    case BtnId::StartStop:
        fsm.transitionTo(stTestStripSelectTimeStop);
        break;
    default: break;
    }
}

void stTestStripExit() {
    DBG("stTestStripExit");
}


// ------------------------------------
// STATE "TestStripSelectTimeStop"
// ------------------------------------
void stTestStripSelectTimeStopEnter() {
    DBG("stTestStripSelectTimeStopEnter");
}

void stTestStripSelectTimeStopLoop() {

}

void stTestStripSelectTimeStopExit() {
    DBG("stTestStripSelectTimeStopExit");
}


// ------------------------------------
// STATE "TestStripReady"
// ------------------------------------
void stTestStripReadyEnter() {
    DBG("stTestStripReadyEnter");
}

void stTestStripReadyLoop() {

}

void stTestStripReadyExit() {
    DBG("stTestStripReadyExit");
}


// ------------------------------------
// STATE "TestStripRunning"
// ------------------------------------
void stTestStripRunningEnter() {
    DBG("stTestStripRunningEnter");
}

void stTestStripRunningLoop() {

}

void stTestStripRunningExit() {
    DBG("stTestStripRunningExit");
}

