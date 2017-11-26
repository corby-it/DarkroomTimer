#include "buzzer.h"
#include "defs.h"

static const uint32_t noteOnTime = 100;
static const uint32_t pauseTime = 50;

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

