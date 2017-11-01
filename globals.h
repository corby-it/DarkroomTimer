#pragma once
#include "digits.h"
#include "fstop.h"
#include "timer_functions.h"
#include "strip_mode.h"

// Display
extern LiquidCrystal lcd;

// State machine stuff
extern EventDispatcher dispatcher;

extern SetTimeState stSetTime;
extern SetFstopState stSetFstop;

// test strip
extern TestStripStopState stTestStripStop;
extern TestStripSelectStopState stTestStripSelectStop;

extern TestStripTimeState stTestStripTime;
extern TestStripSelectTimeState stTestStripSelectTime;

extern TestStripReadyState stTestStripReady;
extern TestStripRunningState stTestStripRunning;


extern RunningState stRunning;
extern FocusState stFocus;

extern FiniteStateMachine fsm;