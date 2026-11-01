#include <stdio.h>
#include <stdbool.h>
#include "map_loader.h"
#include "map.h"


// a tester made with claude
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <map file>\n", argv[0]);
        return 1;
    }

    Map map = MapInit();

    if (!MapLoader(argv[1], &map)) {
        printf("Failed to load map: %s\n", argv[1]);
        MapFree(&map);
        return 1;
    }

    printf("Map loaded: %s (%zu objects)\n", argv[1], map.count);

    for (size_t i = 0; i < map.count; i++) {
        MapObject *o = &map.objects[i];
        printf("[%zu] pos(%.1f, %.1f, %.1f) size(%.1f, %.1f, %.1f)\n",
               i, o->position.x, o->position.y, o->position.z,
               o->size.x, o->size.y, o->size.z);
    }

    if (!MapFree(&map)) {
        printf("MapFree failed\n");
        return 1;
    }
    return 0;
}