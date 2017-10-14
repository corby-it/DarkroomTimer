#pragma once

class TestStripState : public State {
public:
    virtual void enter() override;
    virtual void loop() override;
    virtual void exit() override;
};


class TestStripSelectTimeState : public State {
public:
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
    uint32_t currBaseTime = 0;
    fstop currStep = Third;

    void updateLcd();
};


class TestStripReadyState : public State {
public:
    virtual void enter() override;
    virtual void loop() override;
    virtual void exit() override;

    void setData(uint32_t time, fstop step);
    void exposureDone();

    void reset() {
        incStep = Third;
        currTime = 0;
        totalTime = 0;
        exposureCounter = 0;
    };

private:
    fstop incStep = Third;
    uint32_t currTime = 0, totalTime = 0;
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

    uint32_t exposureTime;

private:
    static const uint8_t lcdTimeCursorPos = 0;
    uint32_t timerCounter = 0;

    void updateLcd();
};