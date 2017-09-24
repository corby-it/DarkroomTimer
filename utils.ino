#include "utils.h"

uint16_t getMult(digit d) {
    switch (d) {
    case DIG_TENTH: return 1;
    case DIG_ONE: return 10;
    case DIG_TEN: return 100;
    case DIG_HUNDRED: return 1000;
    }
}

String getDigitName(digit d) {
    switch (d) {
    case DIG_TENTH: return "Decimi";
    case DIG_ONE: return "Unita";
    case DIG_TEN: return "Decine";
    case DIG_HUNDRED: return "Centinaia";
    }
}

uint8_t getDigit(uint32_t t, digit d) {
    uint8_t res = 0;
    for (uint8_t i = 0; i <= d; ++i) {
        res = t % 10;
        t /= 10;
    }
    return res;
}

