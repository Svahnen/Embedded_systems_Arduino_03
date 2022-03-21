#include "led.h"

#include <avr/io.h>

void LED_init() {
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
