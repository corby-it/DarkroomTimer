#include "fstop.h"
#include <math.h>

// FStops multipliers
float getFstopMult(fstop f, bool neg) {
    switch (f)
    {
    case Base:      return neg ? 1. : 1.;
    case Third:     return neg ? 0.793700526 : 1.25992105;
    case Half:      return neg ? 0.707106781 : 1.414213562;
    case TwoThird:  return neg ? 0.629960524 : 1.587401052;
    case One:       return neg ? 0.5 : 2;
    case OneAndHalf:return neg ? 0.35355339 : 2.828427125;
    case Two:       return neg ? 0.25 : 4;
    case Three:     return neg ? 0.125 : 8;
    }
}

String getFstopName(fstop f) {
    switch (f)
    {
    case Base:      return "  Base";
    case Third:     return "   1/3";
    case Half:      return "   1/2";
    case TwoThird:  return "   2/3";
    case One:       return "     1";
    case OneAndHalf:return " 1 1/2";
    case Two:       return "     2";
    case Three:     return "     3";
    }
}

String getFstopNameLcd(fstop f) {
    auto val = getFstopName(f);
    
    switch (f)
    {
    case Base: break;
    case Third: 
    case Half:
    case TwoThird:  val[1] = byte(PLUSMINUS_SYM); break;
    case One:
    case Two:
    case Three:     val[3] = byte(PLUSMINUS_SYM); break;
    case OneAndHalf:val[0] = byte(PLUSMINUS_SYM); break;
    }
    
    return val;
}

String getFstopNameLcdStrip(fstop f) {
    auto val = getFstopName(f);

    switch (f)
    {
    case Base: break;
    case Third:
    case Half:
    case TwoThird:  val[1] = '+'; break;
    case One:                
    case Two:                
    case Three:     val[3] = '+'; break;
    case OneAndHalf:val[0] = '+'; break;
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