#pragma once

class TestStripState : public State {
public:
    virtual void enter() override;
    virtual void loop() override;
    virtual void exit() override;
};


class TestStripSelectTimeState : public State {
public:
    TestStripSelectTimeState() : currStep(FStopVal::Third) {}

    virtual void enter() override;
    virtual void loop() override;
    virtual void exit() override;

private:
    static const uint8_t lcdTimeCursorPos = 0;
    static const uint8_t lcdStepCursorPos = 10;
    
    enum cursorPos : uint8_t {
        Hundred = lcdTimeCursorPos,
        Ten = lcdTimeCursorPos + 1,
        One = lcdTimeCursorPos + 2,
        Tenth = lcdTimeCursorPos + 4,
        Step = 15,
    };

    uint8_t currCursorPos = 2;
    Time currBaseTime = 10;
    FStop currStep;

    void updateLcd();
};


class TestStripReadyState : public State {
public:
    virtual void enter() override;
    virtual void loop() override;
    virtual void exit() override;

    void setData(Time time, FStop step);
    void exposureDone();

    void reset() {
        incStep = FStopVal::Third;
        currTime = 0;
        totalTime = 0;
        exposureCounter = 0;
    };

private:
    FStop incStep = FStopVal::Third;
    Time currTime;
    Time totalTime;
    uint8_t exposureCounter = 0;
};


class TestStripRunningState : public State, public TimerHandler {
public:
    virtual void enter() override;
    virtual void loop() override;
    virtual void exit() override;

    virtual void timerEvent() override;

    void reset() {
        exposureTime = 0;
        timerCounter = 0;
    };

    Time exposureTime;

private:
    static const uint8_t lcdTimeCursorPos = 0;
    Time timerCounter;

    void updateLcd();
};