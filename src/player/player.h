#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

//typedef lets me use Player directly without writing struct every time
typedef struct {
    Vector3 position;
    Vector3 playerSize;
    Vector3 velocity;
    float eyeHeight;
    bool OnGround;
    float acceleration;
    float airAcceleration;
    float wishSpeed;
    float wishSpeedLimit;
    float jumpForce;
    float gravity;
    float friction;
    float stopSpeed;
    float speed;
    bool canJump;
    float maxGroundSpeed;
} Player;

Player InitPlayer();


#endif