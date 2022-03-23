#include <avr/io.h>

void adc_init() {
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
}