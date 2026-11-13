#include <renderer.h>
#include "rlgl.h"
#include <GL/gl.h>
#include <stdio.h>

// here comes other drawing too
void Renderer(Map *map, Viewmodel *viewmodel) {
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


void RenderViewmodel(Viewmodel *viewmodel) {
    //draw the viewmodel with different camera
    Camera3D cam = {0};
    cam.position = (Vector3){0.0f, 0.0f, 0.0f};
    cam.target = (Vector3){0.0f, 0.0f, -1.0f};
    cam.up = (Vector3){0.0f, 1.0f, 0.0f};
    cam.fovy = 60.0f; // viewmodel fov
    cam.projection = CAMERA_PERSPECTIVE;

    // flush world
    rlDrawRenderBatchActive();
    glClear(GL_DEPTH_BUFFER_BIT); // wipe depth

    BeginMode3D(cam);
        Vector3 offset = {-0.2f, -0.3f, -0.3f};
        DrawModelEx(viewmodel->model,
                    offset,
                    (Vector3){0, 1, 0}, 90.0f,
                    (Vector3){0.07f, 0.08f, 0.07f},
                    RED);
    
    EndMode3D();
}