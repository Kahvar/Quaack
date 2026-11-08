#include <raylib.h>
#include <raymath.h>
#include <camera.h>
#include <player.h>
#include <math.h> // include math to calculate sin and cos


PlayerCamera InitCamera(Player *player) { // initialize the camera with default values later camera.position follows the player x, y, z and target is configured throught mouse
    PlayerCamera camera = { 0 };
    // to access raylibs camera3D use .raylib_camera
    camera.raylib_camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  // Camera position
    camera.raylib_camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.raylib_camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.raylib_camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.raylib_camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type
    camera.yaw = 0.0f;
    camera.pitch = 0.0f;
    camera.sensitivity = 0.005f;
    camera.currentEyeHeight = player->standingHeight * 0.75; // init currenteyeheight to eyeheight

    return camera; // return the 3d camera
}

// updating camera position with players position
void UpdatePlayerCamera(PlayerCamera *camera, Player *player, float dt) {
    Vector2 mousePos = GetMouseDelta();

    camera->yaw += mousePos.x * camera->sensitivity; // left and right
    camera->pitch -= mousePos.y * camera->sensitivity; // up and down

    if (camera->pitch > 1.569051f) camera->pitch = 1.569051f;   // Clamp the pitch so it doesnt go over
    if (camera->pitch < -1.569051f) camera->pitch = -1.569051f; // clamp it also so it doesnt go under

    float dx = cosf(camera->yaw) * cosf(camera->pitch);
    float dy = sinf(camera->pitch);
    float dz = sinf(camera->yaw) * cosf(camera->pitch);

    Vector3 newTarget = {dx, dy, dz}; // calculate the camera facing from yaw and pitch

    // pick the multiplyer depending on crouching
    float targetEyeHeight = player->crouching
        ? player->crouchHeight * 0.75f
        : player->standingHeight * 0.75f;

    // calculate the difference
    float difference = targetEyeHeight - camera->currentEyeHeight;

    if (fabsf(difference) > 0.01f) {
        float factor = fminf(dt * 8.0f, 1.0f);

        camera->currentEyeHeight = Lerp(camera->currentEyeHeight, targetEyeHeight, factor); // Lerp the currenteyeheight to target eyeheight
    } else {
        camera->currentEyeHeight = targetEyeHeight; // keept the eyeheight
    }
    
    camera->raylib_camera.position = (Vector3){player->position.x, player->position.y + camera->currentEyeHeight, player->position.z};  // snap the camera to players pos

    camera->raylib_camera.target = Vector3Add(newTarget, camera->raylib_camera.position); // calculate target point one unit infront of the cam
}