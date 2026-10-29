#ifndef CAMERA_H
#define CAMERA_H
#include <raylib.h>
#include <player.h>

typedef struct Camera {
    Camera3D raylib_camera;
    float yaw;
    float pitch;
    float sensitivity;
} PlayerCamera; // name goes after closing


PlayerCamera InitCamera(void); // return type my PlayerCamera struct

void UpdatePlayerCamera(PlayerCamera *camera, Player *player); // update the camera with PlayerCamera struct


#endif