#include <renderer.h>
#include <stddef.h>


// here comes other drawing too
void Renderer(Map *map) {
    if (map == NULL) {
        return;
    }
    RenderMap(map);
}

void RenderMap(Map *map) {
    size_t object;
    // loop trough the map and draw the CUBES!!
    for (object = 0; object < map->count; object++) {
        DrawCube(map->objects[object].position, map->objects[object].size.x, map->objects[object].size.y, map->objects[object].size.z, GRAY); // draw each object
    }
}
