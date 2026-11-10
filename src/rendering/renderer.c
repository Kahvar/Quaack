#include <renderer.h>
#include <stddef.h>


// here comes other drawing too
void Renderer(Map *map, Viewmodel *viewmodel) {
    if (map == NULL) {
        return;
    }
    RenderMap(map);
    RenderViewmodel(viewmodel);
}

void RenderMap(Map *map) {
    size_t object;
    // loop trough the map and draw the CUBES!!
    for (object = 0; object < map->count; object++) {
        DrawCube(map->objects[object].position, map->objects[object].size.x, map->objects[object].size.y, map->objects[object].size.z, GRAY); // draw each object
    }
}


void RenderViewmodel(Viewmodel *viewmodel) {
    //draw the hands model from viewmodel
    DrawModel(viewmodel->model, (Vector3){10.0f, 1.0f, 3.0f}, 0.5f, GRAY);
}