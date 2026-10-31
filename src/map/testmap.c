#include <map.h>
#include <stdio.h>

int main(void)
{
    Map map = MapInit();

    printf("Initial count: %zu\n", map.count);
    printf("Initial capacity: %zu\n", map.capacity);

    for (int i = 0; i < 20; i++) {
        MapObject object = {
            .position = { i * 2.0f, 0.0f, 0.0f },
            .size = { 2.0f, 2.0f, 2.0f }
        };

        if (!MapAddObject(&map, object)) {
            printf("Failed to add object %d\n", i);
            return 1;
        }
    }

    printf("Count: %zu\n", map.count);
    printf("Capacity: %zu\n", map.capacity);

    MapFree(&map);

    printf("Objects: %p\n", (void *)map.objects);
    printf("Count: %zu\n", map.count);
    printf("Capacity: %zu\n", map.capacity);

    return 0;
}