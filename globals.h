#pragma once
#include "digits.h"
#include "fstop.h"

// Display
extern LiquidCrystal lcd;

// Counters
extern uint32_t currTime;
extern digit currDigit;
extern fstop currFstop;

extern uint32_t timerCounter;

extern bool running;

// State machine stuff
extern State stSetTime;
extern State stSetFstop;
extern State stTestStrip;
extern State stTestStripSelectTimeStop;
extern State stTestStripReady;
extern State stTestStripRunning;
extern State stRunning;
extern State stFocus;

extern FiniteStateMachine fsm;

extern State* returnState;

