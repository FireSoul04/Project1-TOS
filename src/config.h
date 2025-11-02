#ifndef CONFIG_H
#define CONFIG_H

#define DEBUG

#ifdef DEBUG
#define DEBUG_CALL(x) x
#else
#define DEBUG_CALL(x)
#endif

enum Pin {
    BUTTON1 = 5,
    BUTTON2 = 4,
    BUTTON3 = 3,
    BUTTON4 = 2,

    L1 = 10,
    L2 = 9,
    L3 = 8,
    L4 = 7,

    LS = 11,
    POT = A0
};

#define N_LEDS 5
#define N_BUTTONS 4

#endif