#include "sleep.h"

#include <Arduino.h>
#include <avr/sleep.h>

void wakeUp();

void initSleepMode() {
    
}

void sleep() {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
    sleep_enable();
    sleep_mode();  
    sleep_disable(); 
}

void wakeUp() {
    
}