#include "globals.h"
#include "timer_functions.h"


LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

uint32_t currTime = 0;
digit currDigit = DIG_ONE;
fstop currFstop = fstop::Base;

uint32_t timerCounter = 0;

bool running = false;

// State machine stuff
State stSetTime = State(stSetTimeEnter, stSetTimeLoop, stSetTimeExit);
State stSetFstop = State(stSetFstopEnter, stSetFstopLoop, stSetFstopExit);

State stTestStrip = State(stTestStripEnter, stTestStripLoop, stTestStripExit);
State stTestStripSelectTimeStop = State(stTestStripSelectTimeStopEnter, stTestStripSelectTimeStopLoop, stTestStripSelectTimeStopExit);
State stTestStripReady = State(stTestStripReadyEnter, stTestStripReadyLoop, stTestStripReadyExit);
State stTestStripRunning = State(stTestStripRunningEnter, stTestStripRunningLoop, stTestStripRunningExit);

State stRunning = State(stRunningEnter, stRunningLoop, stRunningExit);
State stFocus = State(stFocusEnter, stFocusLoop, stFocusExit);

FiniteStateMachine fsm = FiniteStateMachine(stSetTime);

State* returnState = &stSetTime;
