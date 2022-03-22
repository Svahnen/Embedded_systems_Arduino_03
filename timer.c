#include "timer.h"

#include <avr/io.h>

void timer0_init() {
    // ...
}

void timer2_init() {
    // Timer mode with 1024 prescaler
    TCCR2B |= (1 << CS20);
    TCCR2B |= (1 << CS21);
    TCCR2B |= (1 << CS22);

    // CTC mode
    TCCR2A &= (1 << WGM20);
    TCCR2A |= (1 << WGM21);
    TCCR2B &= ~(1 << WGM22);

    // 1 1 Set OC2A on compare match
    TCCR2A |= (1 << COM2A0);
    TCCR2A |= (1 << COM2A1);

    OCR2A = 15;  // Set top counter to 16000000/1024*0.001 -1 since it starts at index 0, to get ~1ms
}

int uptimeMs = 0;

void uptimeTick() {
    if (bit_is_set(TIFR2, OCF2A)) {
        uptimeMs++;
        TIFR2 = (1 << OCF2A);  // Reset flag
    }
}