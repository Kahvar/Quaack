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
    bool blockedX;
    bool blockedZ;
    bool blockedY;
    bool hitCeiling;
    bool hitFloor;

    float groundHeight;
    float ceilingHeight;
    Vector3 normal;
    float distance;
} CollisionResult;



CollisionResult CheckNearby(Player *player, Map *map, Vector3 new_pos, Vector3 pSize);

CollisionResult CheckAABB(Player *player, MapObject *object, Vector3 new_pos, Vector3 pSize);


#endif