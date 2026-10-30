#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <raylib.h>

typedef struct PlayerInput {
    bool forward;
    bool backward;
    bool left;
    bool right;
    bool jump;
} PlayerInput;

PlayerInput CheckKeys();

#endif