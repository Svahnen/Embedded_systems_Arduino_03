#include "button.h"

#include <avr/io.h>
#include <stdio.h>

#include "timer.h"

void button_init() {
    DDRD &= ~(1 << PB2);  // Set PB2 as input
}

int buttonTimestamp = 0;

void button1() {
    if (bit_is_set(PIND, PD2)) {
        if (buttonTimestamp == 0) {
            buttonTimestamp = uptimeMs;
            printf("pushed\r\n");
            PRR |= (1 << PRADC);
        }
    } else if (buttonTimestamp != 0 && uptimeMs - buttonTimestamp > 10) {  // 10ms debounce
        printf("released\r\n");
        buttonTimestamp = 0;
    }
}