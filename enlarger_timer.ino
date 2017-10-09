#define DEBUGGING
#include <LiquidCrystal.h>
#include <FSM\FiniteStateMachine.h>

#include "defs.h"
#include "btns.h"
#include "globals.h"


void setup() {
    DBG_START();
    pinMode(PIN_LED, OUTPUT);
    
    // TIMER
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = TIMER_START; // start value to get an interrupt every 0.1 seconds
    TCCR1B |= (1 << CS10) | (1 << CS11); // set prescaler to 64
    TIMSK1 |= (1 << TOIE1); // enable timer overflow interrupt

    lcd.begin(16, 2);
    lcd.println("Ciao corby");
}

// ------------------------------------

void loop() {
    fsm.update();
}

// timer1 overflow interrupt
ISR(TIMER1_OVF_vect) {
    TCNT1 = TIMER_START; // start value to get an interrupt every 0.1 seconds

    if (running) {
        if (timerCounter < currTime) {
            timerCounter++;
            DBG(String("Running: ") + t2s(timerCounter) + "/" + t2s(currTime));
        }
        else {
            fsm.transitionTo(*returnState);
        }
    }
}
