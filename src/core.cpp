#include "core.h"

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "config.h"

constexpr int leds[N_LEDS] = { L1, L2, L3, L4, LS };

GameStates state = STARTING;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

void initCore() {
    for (int i = 0; i < N_LEDS; i++) {
        pinMode(leds[i], OUTPUT);
    }
}

void initLCD() {
    lcd.init();
    lcd.backlight();
}