#include <Arduino.h>

#include "config.h"

#include "start.h"
#include "core.h"
#include "play.h"
#include "input.h"
#include "sleep.h"

GameStates state;

void setup() {
    initCore();
    initInput();
    initLCD();
    initSleepMode();
}

void loop() {
    switch (state) {
    case STARTING:
        start();
        break;
    
    case PLAYING:
        play();
        break;

    case TERMINATING:
        terminate();
        break;

    case SLEEPING:
        sleep();
        break;
    }
}
