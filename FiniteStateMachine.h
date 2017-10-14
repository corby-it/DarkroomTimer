#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define NO_ENTER (0)
#define NO_UPDATE (0)
#define NO_EXIT (0)

#define FSM FiniteStateMachine

//define the functionality of the states
class State {
public:
	virtual void enter() = 0;
	virtual void loop() = 0;
	virtual void exit() = 0;
};


class TimerHandler {
public:
    virtual void timerEvent() = 0;
};


class EventDispatcher {
    TimerHandler *currHandler = nullptr;

public:
    void subscribe(TimerHandler& obj) {
        currHandler = &obj;
    };

    void unsubscribe(TimerHandler& obj) {
        if (&obj == currHandler)
            currHandler = nullptr;
    }

    void dispatch() {
        if (currHandler)
            currHandler->timerEvent();
    };
};

//define the finite state machine functionality
class FiniteStateMachine {
	public:
		FiniteStateMachine(State& current);
		
		FiniteStateMachine& loop();
		FiniteStateMachine& transitionTo( State& state );
		FiniteStateMachine& immediateTransitionTo( State& state );
		
		State& getCurrentState();
		boolean isInState( State &state ) const;
		
		unsigned long timeInCurrentState();
		
	private:
		bool 	needToTriggerEnter;
		State* 	currentState;
		State* 	nextState;
		unsigned long stateChangeTime;
};