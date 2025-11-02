#ifndef INPUT_H
#define INPUT_H

enum Buttons {
    B1_INDEX,
    B2_INDEX,
    B3_INDEX,
    B4_INDEX
};

void initInput();
void setupInputInterrupt(bool *buttonEnabled);
void debouncingHandler(int i);
bool isButtonPressed(int buttonIndex);

void debouncingHandler0() { debouncingHandler(0); }
void debouncingHandler1() { debouncingHandler(1); }
void debouncingHandler2() { debouncingHandler(2); }
void debouncingHandler3() { debouncingHandler(3); }

#endif