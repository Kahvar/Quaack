#ifndef RENDERER_H
#define RENDERER_H

#include <raylib.h>
#include <map/map.h>
#include <viewmodel/viewmodel.h>

void Renderer(Map *map, Viewmodel *viewmodel);
void RenderMap(Map *map);
void RenderViewmodel(Viewmodel *viewmodel);

#endif