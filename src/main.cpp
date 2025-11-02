#include <Arduino.h>

#include "config.h"

#include "core.h"
#include "input.h"

#include "start.h"
#include "play.h"
#include "termination.h"
#include "sleep.h"

extern GameState state;

void setup() {
    initCore();
    initInput();
    initLCD();
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

    default:
        break;
    }
}
