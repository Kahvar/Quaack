#include <collision.h>
#include <math.h>
#include <stdio.h>
CollisionResult CheckNearby(Player *player, Map *map, Vector3 new_pos, Vector3 pSize) {
    CollisionResult result = { 0 };

    // later make the seperate the map objects into a 2d grid to check them faster now its fine because the map is small
    for (size_t i = 0; i < map->count; i++) {
        MapObject *object = &map->objects[i];

        CollisionResult current = CheckAABB(player, object, new_pos, pSize);

        if (current.hit && current.normal.x != 0) {
            result.blockedX = true;
        }

        if (current.hit && current.normal.y != 0) {
            result.blockedY = true;
        }
        
        if (current.hit && current.normal.z != 0) {
            result.blockedZ = true;
        }

        // if the player hits a box or is grounded
        if (current.hit || current.grounded) {
            // if the previous or current result is true keep the result true
            result.grounded = result.grounded || current.grounded;
            result.hit = result.hit || current.hit;
        }

        // keep the highest valid surface
        if (current.landed) {
            if (!result.landed || current.groundHeight > result.groundHeight) {
                result.groundHeight = current.groundHeight;
            }

            result.landed = true;
        }
        
        if (current.hitCeiling) {
            if (!result.hitCeiling || current.ceilingHeight < result.ceilingHeight) {
                result.ceilingHeight = current.ceilingHeight;
            }

            result.hitCeiling = true;

        } else if (current.hit && current.normal.y > 0){
            result.hitFloor = true;
        }

    }
    return result;
}

CollisionResult CheckAABB(Player *player, MapObject *object, Vector3 new_pos, Vector3 pSize) {
    CollisionResult result = { 0 };

    float p_minX = new_pos.x - pSize.x / 2;
    float p_maxX = new_pos.x + pSize.x / 2;
    float p_minY = new_pos.y;                          // use position.y because its players feet
    float p_maxY = new_pos.y + pSize.y;
    float p_minZ = new_pos.z - pSize.z / 2;
    float p_maxZ = new_pos.z + pSize.z / 2;

    float b_minX = object->position.x - object->size.x / 2;
    float b_maxX = object->position.x + object->size.x / 2;
    float b_minY = object->position.y - object->size.y / 2;
    float b_maxY = object->position.y + object->size.y / 2;
    float b_minZ = object->position.z - object->size.z / 2;
    float b_maxZ = object->position.z + object->size.z / 2;

    bool collisionX = (p_minX <= b_maxX) && (p_maxX >= b_minX); // if p_min or max hits box max or min true same for all dirs
    bool collisionY = (p_minY < b_maxY) && (p_maxY >= b_minY);
    bool collisionZ = (p_minZ <= b_maxZ) && (p_maxZ >= b_minZ);

    result.groundHeight = b_maxY;
    result.ceilingHeight = b_minY;
    bool hitCeiling = collisionX && collisionZ && player->position.y + pSize.y <= b_minY && new_pos.y + pSize.y > b_minY && player->velocity.y > 0.0f;

    // if hitCeiling is true return early
    if (hitCeiling) {
        result.hit = true;
        result.hitCeiling = true;
        result.normal = (Vector3){0, -1, 0};
        
        return result;
    }
    

    if (collisionX && collisionY && collisionZ) { // AABB collision
        result.hit = true; // it hit something

        float overlapX = fminf(p_maxX, b_maxX) - fmaxf(p_minX, b_minX);
        float overlapY = fminf(p_maxY, b_maxY) - fmaxf(p_minY, b_minY);
        float overlapZ = fminf(p_maxZ, b_maxZ) - fmaxf(p_minZ, b_minZ);

        int smallest = 0; // X

        if(overlapY < overlapX) {
            smallest = 1; // Y
        } 

        if((smallest  == 0 && overlapZ < overlapX) ||
        (smallest == 1 && overlapZ < overlapY)) {
            smallest = 2; // Z only assign smallest to 2 if its really smaller than both
        }

        // x collision
        if(smallest == 0) {
            if (new_pos.x > object->position.x) {
                result.normal = (Vector3){1, 0, 0};
            } else {
                result.normal = (Vector3){-1, 0, 0};
            }
        } else if (smallest == 1) { // Y collision
            // player is landing on top of a box
            if (player->position.y > result.groundHeight && new_pos.y <= result.groundHeight && player->velocity.y < 0){
                result.landed = true;
                result.normal = (Vector3){0, 1, 0};
            }
        } else { // Z collision if smallest = 2
            if (new_pos.z > object->position.z) { 
                result.normal = (Vector3){0, 0, 1};
            } else {
                result.normal = (Vector3){0, 0, -1};
            }
        }
        
        return result;
    }

    result.distance = new_pos.y - result.groundHeight;

    // if the player is on top of a box return grounded true
    if(fabsf(result.distance) < 0.001 && collisionX && collisionZ && player->velocity.y <= 0.0f) {
        result.grounded = true;
    }

    return result;
}
