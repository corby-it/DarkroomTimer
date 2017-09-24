#define DEBUGGING
#include <FSM\FiniteStateMachine.h>

#include "defs.h"
#include "btns.h"
#include "utils.h"

uint32_t currTime = 0;
uint32_t timerCounter = 0;
digit currDigit = DIG_ONE;

bool running = false;

// State machine stuff
void stSetTimeEnter();
void stSetTimeLoop();

void stRunningEnter();
void stRunningLoop();
void stRunningExit();

void stFocusEnter();
void stFocusLoop();
void stFocusExit();

State stSetTime = State(stSetTimeEnter, stSetTimeLoop, NULL);
State stRunning = State(stRunningEnter, stRunningLoop, stRunningExit);
State stFocus = State(stFocusEnter, stFocusLoop, stFocusExit);

FiniteStateMachine fsm = FiniteStateMachine(stSetTime);

State& returnState = stSetTime;


void setup() {
    DBG_START();
    pinMode(PIN_LED, OUTPUT);
    
    // TIMER
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = TIMER_START; // start value to get an interrupt every 0.1 seconds
    TCCR1B |= (1 << CS10) | (1 << CS11); // set prescaler to 64
    TIMSK1 |= (1 << TOIE1); // enable timer overflow interrupt

    DBG(getDigitName(currDigit));
}

void turnOn() {
    digitalWrite(PIN_LED, HIGH);
    running = true;
}

void turnOff() {
    digitalWrite(PIN_LED, LOW);
    running = false;
    timerCounter = 0;
}

// ------------------------------------
// STATE "Set Time"
// ------------------------------------

void stSetTimeEnter()
{
    DBG("stSetTimeEnter");
    returnState = stSetTime;
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
        DBG(currTime);
        break;
    case BtnId::Down:
        currTime -= getDigit(currTime, currDigit) != 0 ? getMult(currDigit) : 0;
        DBG(currTime);
        break;
    case BtnId::Focus:
        fsm.transitionTo(stFocus);
        break;
    case BtnId::StartStop:
        fsm.transitionTo(stRunning);
        break;
    }
}


// ------------------------------------
// STATE "Running"
// ------------------------------------

void stRunningEnter() {
    digitalWrite(PIN_LED, HIGH);
    running = true;
    DBG("stRunningEnter");
}

void stRunningLoop() {
    if (getInput() == BtnId::StartStop)
        fsm.transitionTo(returnState);
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
        fsm.transitionTo(returnState);
}

void stFocusExit() {
    DBG("stFocusExit");
    digitalWrite(PIN_LED, LOW);
}

// ------------------------------------

void loop() {
    fsm.update();
}

// timer1 overflow interrupt
ISR(TIMER1_OVF_vect) {
    TCNT1 = TIMER_START; // start value to get an interrupt every 0.1 seconds

    if (running) {
        if (timerCounter < currTime) {
            timerCounter++;
            DBG(String("Running: ") + String(timerCounter) + String("/") + String(currTime));
        }
        else {
            fsm.transitionTo(returnState);
        }
    }
}
