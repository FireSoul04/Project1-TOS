#ifndef INPUT_H
#define INPUT_H

enum Button {
    B1_INDEX,
    B2_INDEX,
    B3_INDEX,
    B4_INDEX
};

void initInput();
void setupInputInterrupt(bool *buttonEnabled);
void clearInterrupts();
void clearButtonStates();
void debouncingHandler(int i);
bool isButtonPressed(int buttonIndex);

#endif