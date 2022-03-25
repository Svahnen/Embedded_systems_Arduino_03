#include "state.h"

#include <avr/io.h>

#include "adc.h"

int currentState = 1;

void nextState() {
    if (currentState == 4) {
        currentState = 1;
    } else {
        currentState++;
    }
}

void stateRoutine() {
    if (currentState == 1) {
        /* code */
    } else if (currentState == 2) {
        OCR0A = adc_value;
    } else if (currentState == 3) {
        /* code */
    } else if (currentState == 4) {
        /* code */
    }
}

void stateAction() {
    if (currentState == 1) {
        /* code */
    } else if (currentState == 2) {
        /* code */
    } else if (currentState == 3) {
        /* code */
    } else if (currentState == 4) {
        /* code */
    }
}