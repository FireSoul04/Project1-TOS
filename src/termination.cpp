#include "termination.h"

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "config.h"
#include "core.h"
#include "play.h"

#define WAIT_FOR_GAME_OVER 2 // Seconds
#define WAIT_FOR_NEW_GAME 10 // Seconds

extern LiquidCrystal_I2C lcd;
extern int score;

void terminate() {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Game Over!");
    lcd.setCursor(0, 1);
    lcd.print("Score: ");
    lcd.print(score);
    digitalWrite(LS, HIGH);
    delay(WAIT_FOR_GAME_OVER * ONE_SEC_MILLIS);
    digitalWrite(LS, LOW);
    delay((WAIT_FOR_NEW_GAME - WAIT_FOR_GAME_OVER) * ONE_SEC_MILLIS);
    changeState(STARTING);
}