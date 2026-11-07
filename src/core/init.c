#include <raylib.h>

void Init_Window() {
    int SCREEN_WIDTH = 1080;
    int SCREEN_HEIGHT = 720;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game");
    SetTargetFPS(60);
    DisableCursor();
}