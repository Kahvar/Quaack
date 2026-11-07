#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <player/player.h>
#include <core/input.h>
#include <map/map.h>
#include <raylib.h>
#include <raymath.h>

Vector3 GetWishDir(PlayerInput input, float yaw);

void UpdateMovement(Player *player, PlayerInput input,Vector3 wishDir, float dt, Map *map);

void Gravity(Player *player, float dt);

void Friction(Player *player, PlayerInput input, float dt);

void GroundMovement(Player *player, Vector3 wishDir, float dt);

void AirMovement(Player *player, Vector3 wishDir, float dt);

bool GroundCheck(Player *player);

void Jump(Player *player);

void UpdateCrouch(Player *player, bool crouchInput, Map *map);

void Crouch(Player *player);

#endif