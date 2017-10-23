#pragma once
#include "FiniteStateMachine.h"
#include "digits.h"
#include "fstop.h"


class Time {
public:
    Time(uint32_t time = 0) : t(time) {};
    Time(const Time&) = default;
    Time(Time&&) = default;
    Time& operator=(const Time&) = default;
    Time& operator=(Time&&) = default;

    Time& operator=(uint32_t time) { t = time; };

    Time& operator++() {
        t = add(1); 
        return *this;
    }
    Time operator++(int) {
        Time tmp(*this);
        operator++(); 
        return tmp;
    }

    Time& operator--() { 
        t = sub(1);
        return *this;
    }
    Time operator--(int) {
        Time tmp(*this);
        operator--();
        return tmp;
    }

    // SUM
    Time operator+(uint32_t amount) const { 
        return Time(add(amount)); 
    }
    Time operator+(const Time& other) const {
        return Time(t) + other.t;
    }
    Time operator+(FStop f) const { 
        uint32_t new_t = min(round(t * f.mult(false)), MAX_TIMER_TIME);
        return Time(new_t);
    } 
    Time& operator+=(uint32_t amount) { 
        t = add(amount);
        return *this;
    }
    Time& operator+=(FStop f) {
        t = min(round(t * f.mult(false)), MAX_TIMER_TIME);
        return *this;
    }

    // SUB
    Time operator-(uint32_t amount) const {
        return Time(sub(amount));
    }
    Time operator-(const Time& other) const {
        return Time(t) - other.t;
    }
    Time operator-(FStop f) const {
        uint32_t new_t = min(round(t * f.mult(true)), MAX_TIMER_TIME);
        return Time(new_t);
    }
    Time& operator-=(uint32_t amount) {
        t = sub(amount);
        return *this;
    }
    Time& operator-=(FStop f) {
        t = min(round(t * f.mult(true)), MAX_TIMER_TIME);
        return *this;
    }

    bool operator==(const Time& other) const { return other.t == t; }
    bool operator!=(const Time& other) const { return !operator==(other); }
    bool operator<(const Time& other) const { return t < other.t; }

    uint32_t time() const { 
        return t;
    }

    float stops() const {
        return log(t*0.1) / log(2);
    }
    
    String str(bool withSec = true) {
        auto res = String(t / 10) + "." + t % 10;
        if (res.length() == 3)
            res = "00" + res;
        else if (res.length() == 4)
            res = "0" + res;

        return withSec ? res + "s" : res;
    }

    String stopsStr() {
        int32_t fval_trunc = stops() * 100;
        int32_t fval_dec = abs(fval_trunc % 100);

        String res = "";
        res += fval_trunc > 0 ? " " : "";
        res += fval_trunc / 100;
        res += ".";
        res += (fval_dec >= 10 ? "" : "0") + String(fval_dec);
        return res;
    }
    
    uint8_t getDigit(digit d) {
        uint8_t res = 0;
        uint32_t tmp = t;
        for (uint8_t i = 0; i <= d; ++i) {
            res = tmp % 10;
            tmp /= 10;
        }
        return res;
    }

private:
    uint32_t t = 0;

    uint32_t add(uint32_t amount) const {
        uint32_t tmp = t + amount;
        return min(tmp, MAX_TIMER_TIME);
    }
    uint32_t sub(uint32_t amount) const {
        int32_t tmp = t - amount;
        return max(tmp, MIN_TIMER_TIME);
    }
};


class SplashScreenState : public State {
public:
    virtual void enter() override;
    virtual void loop() override;
    virtual void exit() override;
};


class SetTimeState : public State {
public:
    virtual void enter() override;
    virtual void loop() override;
    virtual void exit() override;

    friend class SetFstopState;

private:
    static const uint8_t lcdTimeCursorPos = 5;
    digit currDigit = DIG_ONE;
    Time currTime;

    void updateLcd();
};


class SetFstopState : public State {
public:
    virtual void enter() override;
    virtual void loop() override;
    virtual void exit() override;

private:
    static const uint8_t lcdStepCursorPos = 10;
    static const uint8_t lcdStopCursorPos = 0;
    static const uint8_t lcdTimeCursorPos = 9;

    FStop currFstop;

    void updateLcd();
};


class RunningState : public State, public TimerHandler {
public:
    virtual void enter() override;
    virtual void loop() override;
    virtual void exit() override;

    virtual void timerEvent() override;

    void updateLcd();
    
    State *returnState;
    Time exposureTime;
private:
    static const uint8_t lcdTimeCursorPos = 0;
    Time timerCounter;

};


class FocusState : public State {
public:
    virtual void enter() override;
    virtual void loop() override;
    virtual void exit() override;

    State *returnState;
};