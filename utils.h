#pragma once

#include "defs.h"

#define DIG_TENTH	0
#define DIG_ONE		1
#define DIG_TEN		2
#define DIG_HUNDRED 3

typedef uint8_t digit;

uint16_t getMult(digit d);
String getDigitName(digit d);
uint8_t getDigit(uint32_t t, digit d);
