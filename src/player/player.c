#include <player.h>

Player InitPlayer() {
    Player player = {0}; // later init the player position to the maps start point
    player.position.y = 10.0f;
    player.acceleration = 10.0f;
    player.airAcceleration = 7.0f;
    player.wishSpeed = 7.0f;
    player.jumpForce = 8.0f;
    player.gravity = -9.8f;
    player.friction = 8.0f;
    player.jumpForce = 4.0f;
    player.maxGroundSpeed = 9.0f;
    return player;
}