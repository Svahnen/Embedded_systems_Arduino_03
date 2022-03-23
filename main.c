#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "button.h"
#include "led.h"
#include "serial.h"
#include "timer.h"

volatile uint8_t adc_value = 0;
ISR(ADC_vect) {
    adc_value = ADCH;
}

int main(void) {
    // On my shield I need to jump from thease ports to different ports and thus I set thease to inputs and have them here in main where they will always run and are visable.
    DDRB &= ~(1 << PB3);  // Set PB3 as input
    DDRB &= ~(1 << PB0);  // Set PB0 as input
                          // My specific shield config ends here

    // ADC_init

    // AVCC with external capacitor at AREF pin
    ADMUX |= (1 << REFS0);
    ADMUX &= ~(1 << REFS1);

    // MUX: Analog Channel Selection 0000 per default

    // ADPSn: ADC Prescaler Select [n = 2:0], ADPS[2:0] 011 = 8, page 320 in datasheet
    ADCSRA |= (1 << ADPS0);
    ADCSRA |= (1 << ADPS1);
    // ADCSRA &= ~(1 << ADPS2);

    // Write one to ADLAR to left adjust the result, page 317 in datasheet
    ADMUX |= (1 << ADLAR);

    // Enable interrupt
    ADCSRA |= (1 << ADIE);

    // Enable ADC
    ADCSRA |= (1 << ADEN);

    sei();  // Enable global interrupts
    button_init();
    LED_init();
    uart_init();
    timer0_init();
    timer2_init();

    while (1) {
        uptimeTick();  // Update global var uptimeMS
        button1();     // See if button1 is pressed and act on in
        printf("%d", adc_value);
        ADCSRA |= (1 << ADSC);  // Trigger ADC
    }
}
