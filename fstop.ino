#include "fstop.h"
#include <math.h>

// FStops multipliers
//float getFstopMult(FStop f, bool sub) {
//    switch (f)
//    {
//    case FStop::Base:      return sub ? 1. : 1.;
//    case FStop::Third:     return sub ? 0.793700526 : 1.25992105;
//    case FStop::Half:      return sub ? 0.707106781 : 1.414213562;
//    case FStop::TwoThird:  return sub ? 0.629960524 : 1.587401052;
//    case FStop::One:       return sub ? 0.5 : 2;
//    case FStop::OneAndHalf:return sub ? 0.35355339 : 2.828427125;
//    case FStop::Two:       return sub ? 0.25 : 4;
//    case FStop::Three:     return sub ? 0.125 : 8;
//    }
//}
//
//String getFstopName(FStop f) {
//    switch (f)
//    {
//    case FStop::Base:      return "  Base";
//    case FStop::Third:     return "   1/3";
//    case FStop::Half:      return "   1/2";
//    case FStop::TwoThird:  return "   2/3";
//    case FStop::One:       return "     1";
//    case FStop::OneAndHalf:return " 1 1/2";
//    case FStop::Two:       return "     2";
//    case FStop::Three:     return "     3";
//    }
//}
//
//String getFstopNameLcd(FStop f) {
//    auto val = getFstopName(f);
//    
//    switch (f)
//    {
//    case FStop::Base: break;
//    case FStop::Third: 
//    case FStop::Half:
//    case FStop::TwoThird:  val[1] = byte(PLUSMINUS_SYM); break;
//    case FStop::One:
//    case FStop::Two:
//    case FStop::Three:     val[3] = byte(PLUSMINUS_SYM); break;
//    case FStop::OneAndHalf:val[0] = byte(PLUSMINUS_SYM); break;
//    }
//    
//    return val;
//}
//
//String getFstopNameLcdStrip(FStop f) {
//    auto val = getFstopName(f);
//
//    switch (f)
//    {
//    case FStop::Base: break;
//    case FStop::Third:
//    case FStop::Half:
//    case FStop::TwoThird:  val[1] = '+'; break;
//    case FStop::One:                
//    case FStop::Two:                
//    case FStop::Three:     val[3] = '+'; break;
//    case FStop::OneAndHalf:val[0] = '+'; break;
//    }
//
//    return val;
//}


//
//Time f2t(float fval) {
//    return Time(pow(2, fval));
//}
//
//String t2flcd(Time tval) {
//    return t2flcd(tval.time());
//}

//String t2flcd(uint32_t tval) {
//    int32_t fval_trunc = t2f(tval) * 100;
//    int32_t fval_dec = abs(fval_trunc % 100);
//
//    String res = "";
//    res += fval_trunc > 0 ? " " : "";
//    res += fval_trunc / 100;
//    res += ".";
//    res += (fval_dec >= 10 ? "" : "0") + String(fval_dec);
//    return res;
//}