#ifndef CORE_H
#define CORE_H

#define ONE_SEC_MILLIS 1000

enum GameState {
    STARTING,
    PLAYING,
    TERMINATING,
    SLEEPING,
    
    N_STATES
};

enum Difficulty {
    EASY,
    MEDIUM,
    HARD,
    IMPOSSIBLE,

    N_DIFFICULTIES
};

void initCore();
void initLCD();

void turnOffAllLeds();
long getTimeInState();
void changeState(GameState newState);
bool isJustEnteredInState();

#endif