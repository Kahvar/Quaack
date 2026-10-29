#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <player.h>
#include <core/input.h>
#include <raylib.h>
#include <raymath.h>

Vector3 GetWishDir(PlayerInput input, float yaw);
void UpdateMovement(Player *player, Vector3 wishDir, float dt);
void GroundMovement(Player *player, Vector3 wishDir, float dt);
void AirMovement(Player *player, Vector3 wishDir, float dt);
void GroundCheck(Player *player);
void Jump(Player *player, PlayerInput input, float dt);

#endif