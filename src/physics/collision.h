#ifndef COLLISION_H
#define COLLISION_H

#include <raylib.h>
#include <player/player.h>
#include <map/map.h>
#include <stdbool.h>

bool CheckNearby(Player *player, Map *map, Vector3 new_pos);

bool CheckAABB(Player *player, MapObject *object, Vector3 new_pos);


#endif