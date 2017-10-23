#pragma once

//enum fstop : uint8_t {
//    Base = 0,
//    Third = 1,
//    Half = 2,
//    TwoThird = 3,
//    One = 4,
//    OneAndHalf = 5,
//    Two = 6,
//    Three = 7,
//};

enum class FStopVal : uint8_t {
    Base = 0,
    Third = 1,
    Half = 2,
    TwoThird = 3,
    One = 4,
    OneAndHalf = 5,
    Two = 6,
    Three = 7,
};


class FStop {
public:
    FStop(FStopVal val = FStopVal::Base) : f(val) {};


    float mult(bool sub) {
        switch (f)
        {
        case FStopVal::Base:      return sub ? 1. : 1.;
        case FStopVal::Third:     return sub ? 0.793700526 : 1.25992105;
        case FStopVal::Half:      return sub ? 0.707106781 : 1.414213562;
        case FStopVal::TwoThird:  return sub ? 0.629960524 : 1.587401052;
        case FStopVal::One:       return sub ? 0.5 : 2;
        case FStopVal::OneAndHalf:return sub ? 0.35355339 : 2.828427125;
        case FStopVal::Two:       return sub ? 0.25 : 4;
        case FStopVal::Three:     return sub ? 0.125 : 8;
        }
    };

    String name() {
        switch (f)
        {
        case FStopVal::Base:      return "  Base";
        case FStopVal::Third:     return "   1/3";
        case FStopVal::Half:      return "   1/2";
        case FStopVal::TwoThird:  return "   2/3";
        case FStopVal::One:       return "     1";
        case FStopVal::OneAndHalf:return " 1 1/2";
        case FStopVal::Two:       return "     2";
        case FStopVal::Three:     return "     3";
        }
    };

    String nameLcd() {
        auto val = name();

        switch (f)
        {
        case FStopVal::Base: break;
        case FStopVal::Third:
        case FStopVal::Half:
        case FStopVal::TwoThird:  val[1] = byte(PLUSMINUS_SYM); break;
        case FStopVal::One:
        case FStopVal::Two:
        case FStopVal::Three:     val[3] = byte(PLUSMINUS_SYM); break;
        case FStopVal::OneAndHalf:val[0] = byte(PLUSMINUS_SYM); break;
        }

        return val;
    }

    String nameLcdStrip() {
        auto val = name();

        switch (f)
        {
        case FStopVal::Base: break;
        case FStopVal::Third:
        case FStopVal::Half:
        case FStopVal::TwoThird:  val[1] = '+'; break;
        case FStopVal::One:
        case FStopVal::Two:
        case FStopVal::Three:     val[3] = '+'; break;
        case FStopVal::OneAndHalf:val[0] = '+'; break;
        }

        return val;
    }

    FStop& operator++() { 
        if (f == FStopVal::Three)
            return *this;

        f = FStopVal(uint8_t(f) + 1);
        return *this;
    }
    FStop operator++(int) {
        FStop tmp(*this);
        operator++();
        return tmp;
    }

    FStop& operator--() {
        if (f == FStopVal::Base)
            return *this;

        f = FStopVal(uint8_t(f) - 1);
        return *this; 
    }
    FStop operator--(int) {
        FStop tmp(*this);
        operator--();
        return tmp;
    }

    FStop& operator=(FStopVal newF) {
        f = newF;
    }

private:
    FStopVal f = FStopVal::Base;
};