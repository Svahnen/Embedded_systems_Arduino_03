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
            printf("Old state %d\r\n", currentState);  // Print old state on press
            nextState();
        }
    } else if (buttonTimestamp != 0 && uptime10Ms - buttonTimestamp > 1) {  // 10ms debounce, this is not perfect since it can go +- 10ms depending on when the next 10ms tick will happen
        printf("New state %d\r\n", currentState);                           // Print new state on release
        buttonTimestamp = 0;
    }
}