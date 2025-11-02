#include "start.h"

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "config.h"
#include "core.h"
#include "input.h"

#define WAIT_TIME_FOR_SLEEP 10 // Seconds

#define STEP_SIZE 5

extern GameState state;
extern LiquidCrystal_I2C lcd;
extern int leds[N_LEDS];
extern int buttons[N_BUTTONS];
extern long entranceStateTime;

int intensity = 0;
int step = STEP_SIZE;

Difficulty difficulty = EASY;
Difficulty oldDifficulty = difficulty;

void printWelcomeMessage();
void pulseLed(int ledPin);
Difficulty setDifficulty();

void start() {
    if (isJustEnteredInState()) {
        printWelcomeMessage();
        turnOffAllLeds();

        bool interrupts[N_BUTTONS] {
            true, false, false, false
        };
        setupInputInterrupt(interrupts);
        intensity = 0;
        step = STEP_SIZE;
    }

    pulseLed(LS);
    difficulty = setDifficulty();
    long dt = getTimeInState();
    if (dt >= WAIT_TIME_FOR_SLEEP * ONE_SEC_MILLIS) {
        changeState(SLEEPING);
    }

    if (isButtonPressed(B1_INDEX)) {
        changeState(PLAYING);
    }
    delay(20);
}

void printWelcomeMessage() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Welcome to TOS!");
    lcd.setCursor(0, 1);
    lcd.print("Press B1 to Start");
}

void pulseLed(int ledPin) {
    intensity += step;
    if (intensity == 255 || intensity == 0) {
        step = -step;
    }
    analogWrite(LS, intensity);
}

Difficulty setDifficulty() {
    Difficulty diff = (Difficulty) map(analogRead(POT), 0, 1023, 0, N_DIFFICULTIES);
    if (diff != oldDifficulty) {
        oldDifficulty = diff;
        entranceStateTime = millis(); // This prevents the game to go to sleep while the player is choosing the difficulty
        DEBUG_CALL(lcd.clear());
        DEBUG_CALL(lcd.setCursor(0, 0));
        DEBUG_CALL(lcd.print("Difficulty: "));
        DEBUG_CALL(lcd.print(diff + 1));
    }
    return diff;
}

void startGame() {
    state = PLAYING;
}
