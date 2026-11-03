#ifndef COLLISION_H
#define COLLISION_H

#include <raylib.h>
#include <player/player.h>
#include <map/map.h>
#include <stdbool.h>

typedef struct CollisionResult {
    bool hit;
    bool landed;
    bool grounded;
    float groundHeight;
    Vector3 normal;
    float distance;
} CollisionResult;



CollisionResult CheckNearby(Player *player, Map *map, Vector3 new_pos);

CollisionResult CheckAABB(Player *player, MapObject *object, Vector3 new_pos);


#endif