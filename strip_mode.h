#pragma once

class TestStripStopState : public State {
public:
    virtual void enter() override;
    virtual void loop() override;
    virtual void exit() override;
};


class TestStripTimeState : public State {
public:
    virtual void enter() override;
    virtual void loop() override;
    virtual void exit() override;
};


class TestStripSelectStopState : public State {
public:
    TestStripSelectStopState() : currStep(FStop::lowest) {}

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


class TestStripSelectTimeState : public State {
public:
    TestStripSelectTimeState() {}

    virtual void enter() override;
    virtual void loop() override;
    virtual void exit() override;

private:
    static const uint8_t lcdTimeCursorPos = 0;
    static const uint8_t lcdStepCursorPos = 10;

    enum cursorPos : uint8_t {
        BaseHundred = lcdTimeCursorPos,
        BaseTen = lcdTimeCursorPos + 1,
        BaseOne = lcdTimeCursorPos + 2,
        BaseTenth = lcdTimeCursorPos + 4,
        StepHundred = lcdStepCursorPos,
        StepTen = lcdStepCursorPos + 1,
        StepOne = lcdStepCursorPos + 2,
        StepTenth = lcdStepCursorPos + 4,
    };

    uint8_t currCursorPos = 2;
    Time currBaseTime = 10;
    Time currStepTime = 10;

    void updateLcd();
};


class TestStripReadyState : public State {
public:
    virtual void enter() override;
    virtual void loop() override;
    virtual void exit() override;

    void setData(Time time, FStop step);
    void setData(Time time, Time step);
    void exposureDone();

    void reset() {
        stopStep = FStop::lowest;
        timeStep = 10;
        currTime = 0;
        totalTime = 0;
        exposureCounter = 0;
    };

private:
    FStop stopStep = FStop::lowest;
    Time timeStep = 10;
    Time currTime;
    Time totalTime;
    uint8_t exposureCounter = 0;

    bool useStop = false;
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