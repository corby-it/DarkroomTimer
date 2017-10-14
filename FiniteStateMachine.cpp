#include "FiniteStateMachine.h" 

//FINITE STATE MACHINE
FiniteStateMachine::FiniteStateMachine(State& current){
	needToTriggerEnter = true;
	currentState = nextState = &current;
	stateChangeTime = 0;
}

FiniteStateMachine& FiniteStateMachine::loop() {
	//simulate a transition to the first state
	//this only happens the first time update is called
	if (needToTriggerEnter) { 
		currentState->enter();
		needToTriggerEnter = false;
	} else {
		if (currentState != nextState){
			immediateTransitionTo(*nextState);
		}
		currentState->loop();
	}
	return *this;
}

FiniteStateMachine& FiniteStateMachine::transitionTo(State& state){
	nextState = &state;
	stateChangeTime = millis();
	return *this;
}

FiniteStateMachine& FiniteStateMachine::immediateTransitionTo(State& state){
	currentState->exit();
	currentState = nextState = &state;
	currentState->enter();
	stateChangeTime = millis();
	return *this;
}

//return the current state
State& FiniteStateMachine::getCurrentState() {
	return *currentState;
}

//check if state is equal to the currentState
boolean FiniteStateMachine::isInState( State &state ) const {
	if (&state == currentState) {
		return true;
	} else {
		return false;
	}
}

unsigned long FiniteStateMachine::timeInCurrentState() { 
	millis() - stateChangeTime; 
}
