#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <raylib.h>


typedef struct Viewmodel {
    Model model;
    ModelAnimation *animations;
    int animCount;
    int animIndex;
    float animFrame;
} Viewmodel;

Viewmodel ViewmodelInit();

void ViewmodelUpdate(Viewmodel *viewmodel, float dt); // use pointer because we change structs objects

void ViewmodelShoot(Viewmodel *viewmodel);

void ViewmodelUnload(Viewmodel *viewmodel);

#endif