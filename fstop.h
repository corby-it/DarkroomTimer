#pragma once


class FStop {
private:
    enum class FStopVal : uint8_t {
        Base = 0,
        Sixth = 1,
        Third = 2,
        Half = 3,
        TwoThird = 4,
        FiveSixth = 5,
        One = 6,
        OneAndOneThird = 7,
        OneAndHalf = 8,
        OneAndTwoThird = 9,
        Two = 10,
        Three = 11,
    };

public:
    static const FStopVal base = FStopVal::Base;
    static const FStopVal lowest = FStopVal::Sixth;
    static const FStopVal highest= FStopVal::Three;


    FStop(FStopVal val = base) : f(val) {};


    float mult(bool sub) {
        switch (f)
        {
        case FStopVal::Base:            return sub ? 1. : 1.;
        case FStopVal::Sixth:           return sub ? 0.890898718 : 1.122462048;
        case FStopVal::Third:           return sub ? 0.793700526 : 1.25992105;
        case FStopVal::Half:            return sub ? 0.707106781 : 1.414213562;
        case FStopVal::TwoThird:        return sub ? 0.629960524 : 1.587401052;
        case FStopVal::FiveSixth:       return sub ? 0.561231024 : 1.781797436;
        case FStopVal::One:             return sub ? 0.5 : 2;
        case FStopVal::OneAndOneThird:  return sub ? 0.396850263 : 2.5198421;
        case FStopVal::OneAndHalf:      return sub ? 0.35355339 : 2.828427125;
        case FStopVal::OneAndTwoThird:  return sub ? 0.314980262 : 3.174802104;
        case FStopVal::Two:             return sub ? 0.25 : 4;
        case FStopVal::Three:           return sub ? 0.125 : 8;
        }
    };

    String name() {
        switch (f)
        {
        case FStopVal::Base:            return F("  Base");
        case FStopVal::Sixth:           return F("   1/6");
        case FStopVal::Third:           return F("   1/3");
        case FStopVal::Half:            return F("   1/2");
        case FStopVal::TwoThird:        return F("   2/3");
        case FStopVal::FiveSixth:       return F("   5/6");
        case FStopVal::One:             return F("     1");
        case FStopVal::OneAndOneThird:  return F(" 1 1/3");
        case FStopVal::OneAndHalf:      return F(" 1 1/2");
        case FStopVal::OneAndTwoThird:  return F(" 1 2/3");
        case FStopVal::Two:             return F("     2");
        case FStopVal::Three:           return F("     3");
        }
    };

    String nameLcd() {
        auto val = name();

        switch (f)
        {
        case FStopVal::Base: break;

        case FStopVal::Sixth:
        case FStopVal::Third:
        case FStopVal::Half:
        case FStopVal::TwoThird:
        case FStopVal::FiveSixth:  val[1] = byte(PLUSMINUS_SYM); break;

        case FStopVal::One:
        case FStopVal::Two:
        case FStopVal::Three:      val[3] = byte(PLUSMINUS_SYM); break;

        case FStopVal::OneAndOneThird:
        case FStopVal::OneAndHalf:
        case FStopVal::OneAndTwoThird:  val[0] = byte(PLUSMINUS_SYM); break;
        }

        return val;
    }

    String nameLcdStrip() {
        auto val = name();

        switch (f)
        {
        case FStopVal::Base: break;

        case FStopVal::Sixth:
        case FStopVal::Third:
        case FStopVal::Half:
        case FStopVal::TwoThird:
        case FStopVal::FiveSixth:  val[1] = '+'; break;

        case FStopVal::One:
        case FStopVal::Two:
        case FStopVal::Three:      val[3] = '+'; break;

        case FStopVal::OneAndOneThird:
        case FStopVal::OneAndHalf:
        case FStopVal::OneAndTwoThird:  val[0] = '+'; break;
        }

        return val;
    }

    FStop& operator++() { 
        if (f == highest)
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
        if (f == base)
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

    bool operator==(FStopVal other) {
        return f == other;
    }
    bool operator!=(FStopVal other) {
        return !operator==(other);
    }

private:
    FStopVal f = base;
};