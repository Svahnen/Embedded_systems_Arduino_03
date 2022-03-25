#include "state.h"

#include <avr/io.h>

#include "adc.h"
#include "led.h"
#include "timer.h"

int currentState = 1;

void nextState() {
    if (currentState == 4) {
        currentState = 1;
    } else {
        currentState++;
    }
}

void stateRoutine() {  // Runns every 10ms
    if (currentState == 1) {
        OCR0A = simple_ramp();
    } else if (currentState == 2) {
        ADCSRA |= (1 << ADSC);  // Trigger ADC
        OCR0A = adc_value;
    } else if (currentState == 3) {
        /* code */
    } else if (currentState == 4) {
        OCR0A = 255;
    }
}

int then = 0;

void stateAction() {  // Runns every main loop
    if (currentState == 1) {
        /* code */
    } else if (currentState == 2) {
        /* code */
    } else if (currentState == 3) {
        if (then == 0) {
            then = uptime10Ms;
            if (OCR0A == 255) {
                OCR0A = 0;
            } else {
                OCR0A = 255;
            }
        } else if (then != 0 && uptime10Ms - then > 100) {  // 1 second
            then = 0;
        }
    } else if (currentState == 4) {
        /* code */
    }
}