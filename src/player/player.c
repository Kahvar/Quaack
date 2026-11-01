#include <player.h>

Player InitPlayer() {
    Player player = {0}; // later init the player position to the maps start point
    player.position.y = 10.0f;
    player.acceleration = 8.0f;
    player.airAcceleration = 3.0f;
    player.wishSpeed = 6.5f;
    player.gravity = -10.0f;
    player.friction = 9.0f;
    player.jumpForce = 4.0f;
    player.maxGroundSpeed = 9.0f;
    return player;
}