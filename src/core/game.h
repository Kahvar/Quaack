#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <player/player.h>
#include <player/camera.h>

void GameRun(PlayerCamera *camera, Player *player); // later no args because camera should go into renderer to keep gameloop and rendering seperate
void GameClose();
void GetKeys();

#endif