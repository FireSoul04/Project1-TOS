#include "core.h"

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "config.h"
#include "input.h"

int leds[N_LEDS] = { L1, L2, L3, L4, LS };

GameState state = STARTING;

long entranceStateTime = 0;
bool justEnteredInState = true;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

void initCore() {
    DEBUG_CALL(Serial.begin(9600));
    for (int i = 0; i < N_LEDS; i++) {
        pinMode(leds[i], OUTPUT);
    }
    randomSeed(analogRead(1));
}

void initLCD() {
    lcd.init();
    lcd.backlight();
}

void turnOffAllLeds() {
    for (int i = 0; i < N_LEDS; i++) {
        digitalWrite(leds[i], LOW);
    }
}

long getTimeInState() {
    return millis() - entranceStateTime;
}

void changeState(GameState newState) {
    state = newState;
    justEnteredInState = true;
    entranceStateTime = millis();
    clearInterrupts();
    turnOffAllLeds();
    lcd.clear();
}

bool isJustEnteredInState() {
    bool check = justEnteredInState;
    justEnteredInState = false;
    return check;
}