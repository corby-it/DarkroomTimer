#include "buzzer.h"
#include "defs.h"

static int noteOnTime = 100;
static int pauseTime = 50;

void playOnTone() {
    digitalWrite(PIN_BUZZER, HIGH);
    delay(noteOnTime);
    digitalWrite(PIN_BUZZER, LOW);
}


void playOffTone() {
    digitalWrite(PIN_BUZZER, HIGH);
    delay(noteOnTime);
    digitalWrite(PIN_BUZZER, LOW);
    delay(pauseTime);
    digitalWrite(PIN_BUZZER, HIGH);
    delay(noteOnTime);
    digitalWrite(PIN_BUZZER, LOW);
}

