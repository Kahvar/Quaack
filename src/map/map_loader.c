#include <stdio.h>
#include <map_loader.h>

bool MapLoader(const char *filename, Map *map) {
    MapObject temp_obj;
    char buffer[256];

    FILE *fptr =  fopen(filename, "r");

    if (fptr == NULL) {
        printf("File pointer is null\n");
        return false;
    }

    // read the file
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {

        // 6 floats for pos and size
        int read = sscanf(buffer, "%f %f %f %f %f %f", &temp_obj.position.x,
                                            &temp_obj.position.y,
                                            &temp_obj.position.z,
                                            &temp_obj.size.x,
                                            &temp_obj.size.y,
                                            &temp_obj.size.z);
        
        if (read != 6) {
            printf("wrong line format: %s\n", buffer);
            fclose(fptr);
            return false;
        } else {
            printf("Line read succesfully\n");
        }
        
        // send the temp_obj to the MapAddObject
        if(MapAddObject(map, temp_obj) == false) {
            printf("MapAddObject failed to add the object\n");
            fclose(fptr);
            return false;
        } else {
            printf("object added succesfully\n");
        }
    }

    // if the reading has a problem return false
    if (ferror(fptr)) {
        printf("Cannot read the file\n");
        fclose(fptr);
        return false;
    }

    fclose(fptr);
    return true;
}