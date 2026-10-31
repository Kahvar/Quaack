
#include <map.h>
#include <stdio.h>
#include <stdlib.h>

// init map to 0
Map MapInit(void) {
     Map map = { 0 };
     map.capacity = 16;

     // malloc the 16 MapObject capacity first
     map.objects = malloc(map.capacity * sizeof(MapObject));

     // if the memory allocation fails return a empty map
     if (map.objects == NULL) {
          printf("Memory allocation failed at malloc.");
          map = (Map){0};
          return map;
     }

     // return the 16 byte map
     return map;
}


// add objects to the map and handle realloc
bool MapAddObject(Map *map, MapObject object) {
     if (map == NULL) { // if the map struct is null
          printf("Map = null?");
          return false;
     } else if (map->count > map->capacity) { // if the count is bigger than capacity
          printf("Object count is bigger what the memory can hold.");
          return false;
     } else if (map->objects == NULL && map->capacity > 0) { // if the objects are null while capacity is more
          printf("Maps memory is NULL while the capacity is %zu!\n", sizeof(map->capacity));
          return false;
     } else if (map->count < map->capacity) { // add objects if there is free space
          map->objects[map->count] = object;
          map->count++;
          return true;
     } else if (map->count == map->capacity) { // allocate new memory for more objects
          MapObject *temp = realloc(map->objects, map->capacity * 2 * sizeof(MapObject));

          if (temp == NULL) {
               printf("Memory realloc failed at realloc.");
               return false;
          }
          // assign the realloc to objects
          map->objects = temp;

          map->objects[map->count] = object;
          map->count++;

          map->capacity = map->capacity * 2; // update the capacity to x2 the size

          return true;
     }
     
     // final path just returns false
     printf("Well this is weird");
     return false;
}

bool MapFree(Map *map) {
     if (map == NULL) {
          printf("Cannot free memory from NULL");
          return false;
     } else {
          // free the memory and put everything back
          free(map->objects);
          map->objects = NULL;
          map->count = 0;
          map->capacity = 0;
          return true;
     }
}