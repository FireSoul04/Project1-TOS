#ifndef CORE_H
#define CORE_H

enum GameStates {
    STARTING,
    PLAYING,
    TERMINATING,
    SLEEPING,
    
    N_STATES
};

void initCore();
void initLCD();

#endif