#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <player/player.h>

void GameRun(Camera3D *camera, Player *player); // later no args because camera should go into renderer to keep gameloop and rendering seperate
void GameClose();

#endif