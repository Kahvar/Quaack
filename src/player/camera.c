#include <raylib.h>
#include <camera.h>
#include <player.h>

Camera3D InitCamera(void) { // initialize the camera with default values later camera.position follows the player x, y, z and target is configured throught mouse
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    return camera; // return the 3d camera
}

// updating camera position with players position
void UpdatePlayerCamera(Camera3D *camera, float dt, Player *player) {
    
    camera->position = player->position;
}