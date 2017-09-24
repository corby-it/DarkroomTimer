#pragma once

#ifdef DEBUGGING
#define DBG(x) Serial.println((x))
#define DBG_START() Serial.begin(115200)
#else
#define DBG(x) 
#define DBG_START() 
#endif

#define TIMER_START 40536

