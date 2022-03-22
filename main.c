#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "led.h"
#include "serial.h"
#include "timer.h"

int main(void) {
    // On my shield I need to jump from thease ports to different ports and thus I set thease to inputs and have them here in main where they will always run and are visable.
    DDRB &= ~(1 << PB3);  // Set PB3 as input
    DDRB &= ~(1 << PB0);  // Set PB0 as input
    // My specific shield config ends here

    DDRD &= ~(1 << PB2);  // Set PB2 as input

    LED_init();
    uart_init();
    timer0_init();
    timer2_init();
    int uptimeMs = 0;
    int buttonTimestamp = 0;

    void uptimeTick() {
        if (bit_is_set(TIFR2, OCF2A)) {
            uptimeMs++;
            TIFR2 = (1 << OCF2A);  // Reset flag
        }
    }

    while (1) {
        uptimeTick();

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
}
