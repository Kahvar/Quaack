#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

//typedef lets me use Player directly without writing struct every time
typedef struct Player
{
    Vector3 position;
    Vector3 velocity;
    bool OnGround;
    float acceleration;
    float airAcceleration;
    float wishSpeed;
    float jumpForce;
} Player;

Player InitPlayer();


#endif