#include "digits.h"

uint32_t getMult(digit d) {
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

//String t2s(uint32_t t) {
//    return String(t / 10) + "." + t % 10 + "s";
//}
//
//String t2slcd(uint32_t t, bool withSec) {
//    auto res = String(t / 10) + "." + t % 10;
//    if (res.length() == 3)
//        res = "00" + res;
//    else if (res.length() == 4)
//        res = "0" + res;
//
//    return withSec ? res + "s" : res;
//}