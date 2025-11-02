#include "sleep.h"

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <avr/sleep.h>

#include "input.h"
#include "config.h"
#include "core.h"

extern GameState state;
extern long entranceStateTime;

extern LiquidCrystal_I2C lcd;

void disablePins();
void enablePins();

void sleep() {
    bool interrupts[N_BUTTONS] {
        true, false, false, false
    };
    setupInputInterrupt(interrupts);
    DEBUG_CALL(Serial.println("ZZZ"));

    disablePins();

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();

    enablePins();

    DEBUG_CALL(Serial.println("Wakeup"));
    
    changeState(STARTING);
}

void disablePins() {
    lcd.noDisplay();
    lcd.noBacklight();
}

void enablePins() {
    lcd.display();
    lcd.backlight();
}