#ifndef MAP_H
#define MAP_H

#include <raylib.h>
#include <stddef.h>
#include <stdbool.h>

// objects of the map (one box)
typedef struct MapObject {
    Vector3 position;
    Vector3 size;
} MapObject;

// collection of boxes
typedef struct Map {
    MapObject *objects;
    size_t count;
    size_t capacity;
} Map;

//returns empty map
Map MapInit(void);

// adds objects to the map structure and handles memory returns a false if realloc fails
bool MapAddObject(Map *map, MapObject object);

bool MapFree(Map *map);

#endif