#include "start.h"

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "config.h"
#include "game.h"
#include "input.h"

#define WAIT_TIME_FOR_SLEEP 10
#define ONE_SEC_MILLIS 1000

#define STEP_SIZE 5

extern GameStates state;
extern LiquidCrystal_I2C lcd;
extern int leds[N_LEDS] = { L1, L2, L3, L4, LS };
extern int buttons[N_BUTTONS] = { B1, B2, B3, B4 };

long waitTime = 0;
int intensity = 0;
int step = STEP_SIZE;

Difficulty difficulty = EASY;

void printWelcomeMessage();
void turnOffAllLeds();
void pulseLed(int ledPin);
Difficulty setDifficulty();

void start() {
    if (waitTime == 0) {
        waitTime = millis();
        printWelcomeMessage();
        turnOffAllLeds();
    }

    pulseLed(LS);
    difficulty = setDifficulty();
    long ts = millis();
    if (ts - waitTime >= WAIT_TIME_FOR_SLEEP * ONE_SEC_MILLIS) {
        state = SLEEPING;
        waitTime = 0;
    }

    if (isButtonPressed(B1_INDEX)) {
        state = PLAYING;
        waitTime = 0;
    }
}

void printWelcomeMessage() {
    lcd.setCursor(2, 0);
    lcd.print("Welcome to TOS!");
    lcd.setCursor(1, 1);
    lcd.print("Press B1 to Start");
}

void turnOffAllLeds() {
    for (int i = 0; i < N_LEDS - 1; i++) {
        digitalWrite(leds[i], LOW);
    }
}

void pulseLed(int ledPin) {
    if (intensity == 255 || intensity == 0) {
        step = -step;
    }
    intensity += step;
    analogWrite(LS, intensity);
}

Difficulty setDifficulty() {
    return (Difficulty) map(analogRead(POT), 0, 1023, 0, N_DIFFICULTIES - 1);   
}

void startGame() {
    state = PLAYING;
}
