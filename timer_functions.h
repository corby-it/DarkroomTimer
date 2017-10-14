#pragma once
#include "FiniteStateMachine.h"
#include "digits.h"
#include "fstop.h"

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

private:
    static const uint8_t lcdTimeCursorPos = 5;
    digit currDigit = DIG_ONE;

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

    fstop currFstop = fstop::Base;

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

private:
    static const uint8_t lcdTimeCursorPos = 0;
    uint32_t timerCounter = 0;

};


class FocusState : public State {
public:
    virtual void enter() override;
    virtual void loop() override;
    virtual void exit() override;

    State *returnState;
};