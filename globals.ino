#include "globals.h"
#include "timer_functions.h"

// Display
LiquidCrystal lcd(
    PIN_LCD_RS, 
    PIN_LCD_ENABLE, 
    PIN_LCD_D4,
    PIN_LCD_D5,
    PIN_LCD_D6,
    PIN_LCD_D7
);

// State machine stuff
EventDispatcher dispatcher;

SplashScreenState stSplashScreen;

SetTimeState stSetTime;
SetFstopState stSetFstop;

// test stip
TestStripStopState stTestStripStop;
TestStripSelectStopState stTestStripSelectStop;

TestStripTimeState stTestStripTime;
TestStripSelectTimeState stTestStripSelectTime;

TestStripReadyState stTestStripReady;
TestStripRunningState stTestStripRunning;


RunningState stRunning;
FocusState stFocus;

FiniteStateMachine fsm = FiniteStateMachine(stSplashScreen);