#ifndef CAMERA_H
#define CAMERA_H
#include <raylib.h>
#include <player.h>


Camera3D InitCamera(void); // return type Camera3D
void UpdatePlayerCamera(Camera3D *camera, float dt, Player *player); // update the camera with the Camera3D from initcamera


#endif