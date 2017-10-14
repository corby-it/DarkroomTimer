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
};


class TestStripReadyState : public State {
public:
    virtual void enter() override;
    virtual void loop() override;
    virtual void exit() override;
};


class TestStripRunningState : public State {
public:
    virtual void enter() override;
    virtual void loop() override;
    virtual void exit() override;
};