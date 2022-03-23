#include "led.h"

#include <avr/io.h>

void LED_init() {
    DDRB &= ~(1 << BLUE);  // Set PB1 (Pin9, blue LED on the shield) in DDRB (Port B Data Direction Register) to 0, this makes PB1 an input so we can jump to a interupt instead
    DDRB &= ~(1 << GREEN);
    DDRD |= (1 << PD6);  // RED is jumped to PD6
}

void LED_toggle(int LED) {
    PORTB ^= (1 << LED);
}

int value = 0;
int ramp = 1;
int simple_ramp() {
    if (ramp) {
        if (value == 255) {
            ramp = 0;
            return value--;
        }
        return value++;
    } else {
        if (value == 0) {
            ramp = 1;
            return value++;
        }
        return value--;
    }
}
