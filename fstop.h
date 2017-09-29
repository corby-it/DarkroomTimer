#pragma once

enum fstop : uint8_t {
    Base = 0,
    Third = 1,
    Half = 2,
    TwoThird = 3,
    One = 4,
    OneAndHalf = 5,
    Two = 6,
    Three = 7,
};

float getFstopMult(fstop f, bool neg);
String getFstopName(fstop f);

uint32_t f2t(float fval);
float t2f(uint32_t tval);

