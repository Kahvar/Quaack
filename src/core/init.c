#include <raylib.h>

void Init_Window() {
    int SCREEN_WIDTH = 720;
    int SCREEN_HEIGHT = 480;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game");
    SetTargetFPS(60);
    DisableCursor();
}