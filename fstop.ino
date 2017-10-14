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
    case 0: return "  Base";
    case 1: return "   1/3";
    case 2: return "   1/2";
    case 3: return "   2/3";
    case 4: return "     1";
    case 5: return " 1 1/2";
    case 6: return "     2";
    case 7: return "     3";
    }
}

String getFstopNameLcd(fstop f) {
    auto val = getFstopName(f);
    
    switch (f)
    {
    case 0: break;
    case 1: 
    case 2:
    case 3: 
        val[1] = byte(PLUSMINUS_SYM);
        break;
    case 4:
    case 6:
    case 7:
        val[3] = byte(PLUSMINUS_SYM);
        break;
    case 5:
        val[0] = byte(PLUSMINUS_SYM);
        break;
    }
    
    return val;
}

uint32_t f2t(float fval) {
    return pow(2, fval);
}

float t2f(uint32_t tval) {
    return log(tval*0.1) / log(2);
}

String t2flcd(uint32_t tval) {
    int32_t fval_trunc = t2f(tval) * 100;
    int32_t fval_dec = abs(fval_trunc % 100);

    String res = "";
    res += fval_trunc > 0 ? " " : "";
    res += fval_trunc / 100;
    res += ".";
    res += (fval_dec >= 10 ? "" : "0") + String(fval_dec);
    return res;
}