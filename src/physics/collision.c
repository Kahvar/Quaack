#include <collision.h>

bool CheckNearby(Player *player, Map *map, Vector3 new_pos) {
    // later make the seperate the map objects into a 2d grid to check them faster now its fine because the map is small
    for (size_t i = 0; i < map->count; i++) {
        MapObject *object = &map->objects[i];

        if(CheckAABB(player, object, new_pos)) {
            return true;
        } 
    }

    return false;
}

bool CheckAABB(Player *player, MapObject *object, Vector3 new_pos) {
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
    bool collisionY = (p_minY <= b_maxY) && (p_maxY >= b_minY);
    bool collisionZ = (p_minZ <= b_maxZ) && (p_maxZ >= b_minZ);

    return collisionX && collisionY && collisionZ; // returns true if all are true how handy
}
