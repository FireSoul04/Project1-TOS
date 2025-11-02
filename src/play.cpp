#include "play.h"

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>

#include "config.h"
#include "core.h"
#include "input.h"
#include "start.h"

#define WAIT_FOR_GAME_START 2 // Seconds
#define WAIT_FOR_NEW_ROUND 2 // Seconds

#define FIRST_ROUND_TIME_OUT 10 // Seconds

long getTimeFactor(Difficulty difficulty, int currentRound);

extern GameState state;
extern LiquidCrystal_I2C lcd;
extern int leds[N_LEDS];
extern int buttons[N_BUTTONS];
extern long entranceStateTime;

extern Difficulty difficulty;

bool newRound;
int currentRound;
int score;

int sequenceArray[N_BUTTONS] = {
    1, 2, 3, 4
};

int buttonsPressed;
long roundStartTime;
long currentTime;
long timeout;

void play() {
    if (isJustEnteredInState()) {
        setupGame();
    }
    if (newRound) {
        setupGameRound();
    }
    gameRound();
}

void setupGame() {
    newRound = true;
    currentRound = 1;
    score = 0;
    timeout = FIRST_ROUND_TIME_OUT * ONE_SEC_MILLIS;
    lcd.setCursor(6, 0);
    lcd.print("Go!");
    delay(WAIT_FOR_GAME_START * ONE_SEC_MILLIS);
}

void setupGameRound() {
    newRound = false;
    if (currentRound > 1) {
        timeout -= getTimeFactor(difficulty, currentRound);
    }
    DEBUG_CALL(Serial.print("timeout: "));
    DEBUG_CALL(Serial.println(timeout));
    currentTime = 0;
    buttonsPressed = 0;
    turnOffAllLeds();
    bool enabledButtons[N_BUTTONS] = { true, true, true, true };
    setupInputInterrupt(enabledButtons);
    shuffle(sequenceArray, N_BUTTONS);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Sequence:");
    lcd.setCursor(6, 1);
    for (int i = 0; i < N_BUTTONS; i++) {
        lcd.print(sequenceArray[i]);
        DEBUG_CALL(Serial.print(sequenceArray[i]));
    }
    DEBUG_CALL(Serial.println());
    roundStartTime = millis();
}

void gameRound() {
    currentTime = millis() - roundStartTime;
    if (currentTime >= timeout) {
        gameOver();
    }
    for (int i = 0; i < N_BUTTONS; i++) {
        if (isButtonPressed(i)) {
            DEBUG_CALL(Serial.print("i + 1: "));
            DEBUG_CALL(Serial.print(i + 1));
            DEBUG_CALL(Serial.print(", seq arr[i]: "));
            DEBUG_CALL(Serial.print(sequenceArray[buttonsPressed]));
            DEBUG_CALL(Serial.println());
            if (i + 1 != sequenceArray[buttonsPressed]) {
                gameOver();
            } else {
                buttonsPressed++;
                digitalWrite(leds[i], HIGH);
            }
        }
    }
    if (buttonsPressed == 4) {
        roundWon();
    }
}

void gameOver() {
    changeState(TERMINATING);
}

void roundWon() {
    currentRound++;
    score++;
    lcd.clear();
    lcd.setCursor(6, 0);
    lcd.print("GOOD!");
    lcd.setCursor(0, 1);
    lcd.print("Score: ");
    lcd.print(score);
    delay(WAIT_FOR_NEW_ROUND * ONE_SEC_MILLIS);
    setupGameRound();
}

void shuffle(int *array, int length) {
    for (int i = 0; i < length; i++) {
        int rand = random(N_BUTTONS);
        int temp = array[i];
        array[i] = array[rand];
        array[rand] = temp;
    }
}

long getTimeFactor(Difficulty difficulty, int currentRound) {
    return long(ONE_SEC_MILLIS * (M_PI_2 - atan(currentRound / double(2 * difficulty + 1))));
}