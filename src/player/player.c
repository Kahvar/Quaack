#include <player.h>

Player InitPlayer() {
    Player player = {0}; // later init the player position to the maps start point
    player.acceleration = 10.0f;
    player.airAcceleration = 10.0f;
    player.wishSpeed = 10.0f;
    player.jumpForce = 8.0f;
    return player;
}