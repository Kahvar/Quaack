#include <player.h>

Player InitPlayer() {
    Player player = {0}; // later init the player position to the maps start point
    player.position.y = 10.0f;
    player.playerSize = (Vector3){1.0f, 3.0f, 1.0f};
    player.eyeHeight = 2.0f;
    player.acceleration = 8.0f;
    player.airAcceleration = 10.0f;
    player.wishSpeed = 9.0f;
    player.wishSpeedLimit = 0.85f;
    player.gravity = -22.0f;
    player.friction = 6.0f;
    player.stopSpeed = 1.0f;
    player.jumpForce = 7.5f;
    player.maxGroundSpeed = 9.0f;
    player.crouching = false;
    return player;
}