//#define DEBUGGING
#include <LiquidCrystal.h>

#include "defs.h"
#include "btns.h"
#include "globals.h"

byte plusMinus[] = {
    B00000,
    B00100,
    B00100,
    B11111,
    B00100,
    B00100,
    B11111,
    B00000,
};


void setup() {
    DBG_START();
    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, LAMP_OFF);

    pinMode(PIN_BUZZER, OUTPUT);
    
    // TIMER
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = TIMER_START; // start value to get an interrupt every 0.1 seconds
    TCCR1B |= (1 << CS10) | (1 << CS11); // set prescaler to 64
    TIMSK1 |= (1 << TOIE1); // enable timer overflow interrupt

    lcd.createChar(7, plusMinus);
    lcd.begin(16, 2);
}

// ------------------------------------

void loop() {
    fsm.loop();
}

// timer1 overflow interrupt
ISR(TIMER1_OVF_vect) {
    TCNT1 = TIMER_START; // start value to get an interrupt every 0.1 seconds
    dispatcher.dispatch();
}
