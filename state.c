#include "state.h"

#include <avr/io.h>

int currentState = 0;

void nextState() {
    if (currentState == 3) {
        currentState = 0;
    } else {
        currentState++;
    }
}