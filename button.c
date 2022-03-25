#include "button.h"

#include <avr/io.h>
#include <stdio.h>

#include "state.h"
#include "timer.h"

void button_init() {
    DDRD &= ~(1 << PB2);  // Set PB2 as input
}

int buttonTimestamp = 0;

void button1() {
    if (bit_is_set(PIND, PD2)) {
        if (buttonTimestamp == 0) {
            buttonTimestamp = uptime10Ms;
            printf("pushed\r\n");
            ADCSRA |= (1 << ADSC);
        }
    } else if (buttonTimestamp != 0 && uptime10Ms - buttonTimestamp > 1) {  // 10ms debounce, this is not perfect since it can go +- 10ms depending on when the next 10ms tick will happen
        printf("released\r\n");
        buttonTimestamp = 0;
    }
}