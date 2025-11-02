#include "input.h"

#include <Arduino.h>
#include <EnableInterrupt.h>

#include "config.h"

constexpr int buttons[N_BUTTONS] = { B1, B2, B3, B4 };

long lastButtonPressTimes[N_BUTTONS] = { 0, 0, 0, 0 };
bool buttonPressed[N_BUTTONS] = { false, false, false, false };

void (*debouncingHandlers[N_BUTTONS])() = { debouncingHandler0, debouncingHandler1, debouncingHandler2, debouncingHandler3 };

void initInput() {
    for (int i = 0; i < N_BUTTONS; i++) {
        pinMode(buttons[i], INPUT);
    }
}

void setupInputInterrupt(bool *buttonEnabled) {
    for (int i = 0; i < N_BUTTONS; i++) {
        disableInterrupt(buttons[i]);
    }

    for (int i = 0; i < N_BUTTONS; i++) {
        if (buttonEnabled[i]) {
            enableInterrupt(buttons[i], debouncingHandlers[i], CHANGE);
        }
    }
}

void debouncingHandler(int i) {
    long ts = millis();
    if (ts - lastButtonPressTimes[i] > BOUNCING_TIME) {
        lastButtonPressTimes[i] = ts;
        int status = digitalRead(buttons[i]);
        if (status == HIGH && !buttonPressed[i]) { 
            buttonPressed[i] = true;
        }
    }
}

bool isButtonPressed(int buttonIndex) {
    return buttonPressed[buttonIndex];
}