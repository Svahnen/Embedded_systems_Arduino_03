#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "adc.h"
#include "button.h"
#include "led.h"
#include "serial.h"
#include "timer.h"

volatile uint8_t adc_value = 0;
ISR(ADC_vect) {
    adc_value = ADCH;
}

ISR(TIMER2_COMPA_vect) {
    OCR0A = adc_value;
    ADCSRA |= (1 << ADSC);  // Trigger ADC
    uptime10Ms++;
}

int main(void) {
    // On my shield I need to jump from thease ports to different ports and thus I set thease to inputs and have them here in main where they will always run and are visable.
    DDRB &= ~(1 << PB3);  // Set PB3 as input
    DDRB &= ~(1 << PB0);  // Set PB0 as input
    // My specific shield config ends here

    sei();  // Enable global interrupts
    button_init();
    LED_init();
    uart_init();
    timer0_init();
    timer2_init();
    adc_init();

    while (1) {
        button1();
    }
}
