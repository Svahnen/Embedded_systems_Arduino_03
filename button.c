#include "button.h"

#include <avr/io.h>
#include <stdio.h>

#include "timer.h"

int buttonTimestamp = 0;

void button1() {
    if (bit_is_set(PIND, PD2)) {
        if (buttonTimestamp == 0) {
            buttonTimestamp = uptimeMs;
            printf("pushed\r\n");
        }
    } else if (buttonTimestamp != 0 && uptimeMs - buttonTimestamp > 10) {  // > "milliseconds"
        printf("released\r\n");
        buttonTimestamp = 0;
    }
}