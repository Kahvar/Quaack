#ifndef CAMERA_H
#define CAMERA_H
#include <raylib.h>
#include <player.h>

typedef struct Camera {
    Camera3D raylib_camera;
    float yaw;
    float pitch;
    float sensitivity;
    float currentEyeHeight;
} PlayerCamera; // name goes after closing


PlayerCamera InitCamera(Player *player); // return type my PlayerCamera struct

void UpdatePlayerCamera(PlayerCamera *camera, Player *player, float dt); // update the camera with PlayerCamera struct


#endif