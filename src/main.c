#include <raylib.h>
#include <core/init.h>
#include <core/game.h>
#include <player/camera.h>
#include <player/player.h>

int main() {
    Init_Window();
    Player player = InitPlayer(); // init player and store it to player
    PlayerCamera camera = InitCamera(); // get the camera from init
    GameRun(&camera, &player); // Run the game with the pointer to camera and player
    return 0;
}