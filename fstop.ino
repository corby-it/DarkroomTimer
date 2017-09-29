#include "fstop.h"
#include <math.h>

// FStops multipliers
float getFstopMult(fstop f, bool neg) {
    switch (f)
    {
    case 0: return neg ? 1. : 1.;
    case 1: return neg ? 0.793700526 : 1.25992105;
    case 2: return neg ? 0.707106781 : 1.414213562;
    case 3: return neg ? 0.629960524 : 1.587401052;
    case 4: return neg ? 0.5 : 2;
    case 5: return neg ? 0.35355339 : 2.828427125;
    case 6: return neg ? 0.25 : 4;
    case 7: return neg ? 0.125 : 8;
    }
}

String getFstopName(fstop f) {
    switch (f)
    {
    case 0: return "Base";
    case 1: return "± 1/3";
    case 2: return "± 1/2";
    case 3: return "± 2/3";
    case 4: return "± 1";
    case 5: return "± 1 1/2";
    case 6: return "± 2";
    case 7: return "± 3";
    }
}

uint32_t f2t(float fval) {
    return pow(2, fval);
}

float t2f(uint32_t tval) {
    return log(tval*0.1) / log(2);
}