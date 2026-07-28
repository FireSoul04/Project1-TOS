#ifndef CONFIG_H
#define CONFIG_H

#define DEBUG

# ifdef DEBUG
#  define DEBUG_CALL(x) x
# else
#  define DEBUG_CALL(x)
# endif

enum Pin {
    BUTTON1 = 3,
    BUTTON2 = 4,
    BUTTON3 = 5,
    BUTTON4 = 6,

    L1 = 7,
    L2 = 8,
    L3 = 9,
    L4 = 10,

    LS = 11,
    POT = A0
};

#define N_LEDS 5
#define N_BUTTONS 4

#endif