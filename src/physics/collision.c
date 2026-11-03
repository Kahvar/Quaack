#include <collision.h>
#include <math.h>
#include <stdio.h>
CollisionResult CheckNearby(Player *player, Map *map, Vector3 new_pos) {
    CollisionResult result = { 0 };

    // later make the seperate the map objects into a 2d grid to check them faster now its fine because the map is small
    for (size_t i = 0; i < map->count; i++) {
        MapObject *object = &map->objects[i];

        result = CheckAABB(player, object, new_pos);

        // if the player hits a box or is grounded
        if (result.hit || result.grounded) {
            return result;
        }

    }
    return result;
}

CollisionResult CheckAABB(Player *player, MapObject *object, Vector3 new_pos) {
    CollisionResult result = { 0 };

    float p_minX = new_pos.x - player->playerSize.x / 2;
    float p_maxX = new_pos.x + player->playerSize.x / 2;
    float p_minY = new_pos.y;                          // use position.y because its players feet
    float p_maxY = new_pos.y + player->playerSize.y;
    float p_minZ = new_pos.z - player->playerSize.z / 2;
    float p_maxZ = new_pos.z + player->playerSize.z / 2;

    float b_minX = object->position.x - object->size.x / 2;
    float b_maxX = object->position.x + object->size.x / 2;
    float b_minY = object->position.y - object->size.y / 2;
    float b_maxY = object->position.y + object->size.y / 2;
    float b_minZ = object->position.z - object->size.z / 2;
    float b_maxZ = object->position.z + object->size.z / 2;

    bool collisionX = (p_minX <= b_maxX) && (p_maxX >= b_minX); // if p_min or max hits box max or min true same for all dirs
    bool collisionY = (p_minY < b_maxY) && (p_maxY >= b_minY);
    bool collisionZ = (p_minZ <= b_maxZ) && (p_maxZ >= b_minZ);

    float playerCenterY = new_pos.y + player->playerSize.y / 2;

    result.groundHeight = b_maxY;

    if (collisionX && collisionY && collisionZ) { // AABB collision
        result.hit = true; // it hit something

        float overlapX = fminf(p_maxX, b_maxX) - fmaxf(p_minX, b_minX);
        float overlapY = fminf(p_maxY, b_maxY) - fmaxf(p_minY, b_minY);
        float overlapZ = fminf(p_maxZ, b_maxZ) - fmaxf(p_minZ, b_minZ);

        printf("Overlap X: %.3f | Y: %.3f | Z: %.3f\n", overlapX, overlapY, overlapZ);

        // x collision
        if(overlapX < overlapY && overlapX < overlapZ) {
            if (new_pos.x > object->position.x) {
                result.normal = (Vector3){1, 0, 0};
            } else {
                result.normal = (Vector3){-1, 0, 0};
            }
        } 

        // z collision
        if(overlapZ < overlapY && overlapZ < overlapX) {
            if (new_pos.z > object->position.z) {
                result.normal = (Vector3){0, 0, 1};
            } else {
                result.normal = (Vector3){0, 0, -1};
            }
        } 

        // y collision
        if(overlapY < overlapX && overlapY < overlapZ) {
            // player is landing on top of a box
            if (player->position.y > result.groundHeight && new_pos.y <= result.groundHeight && player->velocity.y < 0){
                result.landed = true;
            } 
            if(playerCenterY < object->position.y) {
                result.normal = (Vector3){0, -1, 0};
            } else {
            result.normal = (Vector3){0, 1, 0};
            } 
        }
        
        printf("Normal: %.1f %.1f %.1f\n", result.normal.x, result.normal.y, result.normal.z);

    
        //printf("Player Y: %.2f - %.2f | Box Y: %.2f - %.2f\n", p_minY, p_maxY, b_minY, b_maxY);

        return result;
    }

    result.distance = new_pos.y - result.groundHeight;

    // if the player is on top of a box return grounded true
    if(fabsf(result.distance) < 0.001 && collisionX && collisionZ && player->velocity.y <= 0.0f) {
        result.grounded = true;
    }

    return result;
}
