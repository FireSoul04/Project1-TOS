#include "input.h"

#include <Arduino.h>
#include <EnableInterrupt.h>

#include "config.h"
    
#define BOUNCING_TIME 500

int buttons[N_BUTTONS] = { BUTTON1, BUTTON2, BUTTON3, BUTTON4 };

long lastButtonPressTimes[N_BUTTONS] = { 0, 0, 0, 0 };
bool buttonPressed[N_BUTTONS] = { false, false, false, false };

void debouncingHandler1() { debouncingHandler(B1_INDEX); }
void debouncingHandler2() { debouncingHandler(B2_INDEX); }
void debouncingHandler3() { debouncingHandler(B3_INDEX); }
void debouncingHandler4() { debouncingHandler(B4_INDEX); }

void (*debouncingHandlers[N_BUTTONS])() = { debouncingHandler1, debouncingHandler2, debouncingHandler3, debouncingHandler4 };

void initInput() {
    for (int i = 0; i < N_BUTTONS; i++) {
        pinMode(buttons[i], INPUT);
    }
}

void setupInputInterrupt(bool *buttonEnabled) {
    clearInterrupts();
    for (int i = 0; i < N_BUTTONS; i++) {
        if (buttonEnabled[i]) {
            enableInterrupt(buttons[i], debouncingHandlers[i], CHANGE);
        }
    }
}

void clearInterrupts() {
    for (int i = 0; i < N_BUTTONS; i++) {
        disableInterrupt(buttons[i]);
    }
    clearButtonStates();
}

void clearButtonStates() {
    long ts = millis();
    for (int i = 0; i < N_BUTTONS; i++) {
        buttonPressed[i] = false;
        lastButtonPressTimes[i] = ts;
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
    bool pressed = buttonPressed[buttonIndex];
    if (pressed) {
        long ts = millis();
        buttonPressed[buttonIndex] = false;
        lastButtonPressTimes[buttonIndex] = ts;
    }
    return pressed;
}