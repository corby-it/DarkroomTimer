#pragma once

#define VERSION F("v1.0")

#ifdef DEBUGGING
#define DBG(x) Serial.println((x))
#define DBG_START() Serial.begin(115200)
#else
#define DBG(x) 
#define DBG_START() 
#endif

#define TIMER_START     40536

#define MAX_TIMER_TIME  9999
#define MIN_TIMER_TIME  0

#define PLUSMINUS_SYM   7

// PINS
#define PIN_LED			8
#define PIN_BTN_LEFT	12
#define PIN_BTN_RIGHT	11
#define PIN_BTN_UP		9
#define PIN_BTN_DOWN	10
#define PIN_BTN_START	A0
#define PIN_BTN_FOCUS   A1
#define PIN_BTN_MODE    A2
//#define PIN_LCD_BRIGHT  10

#define PIN_LCD_RS      7
#define PIN_LCD_ENABLE  6
#define PIN_LCD_D4      5
#define PIN_LCD_D5      4
#define PIN_LCD_D6      3
#define PIN_LCD_D7      2