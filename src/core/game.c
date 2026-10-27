#include <game.h>
#include <raylib.h>
#include <player/camera.h>


// run the game with player and camera parameters
void GameRun(Camera3D *camera, Player *player) {
    
    Vector3 cubePosition = { 5.0f, 0.0f, 5.0f };

    while(!WindowShouldClose()) {
        float dt = GetFrameTime();

        BeginDrawing();
            ClearBackground(RAYWHITE);

            // update the camera with current camera and player
            UpdatePlayerCamera(camera, dt, player);

            BeginMode3D(*camera);
                DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);

                DrawGrid(10, 1.0f);
                
            EndMode3D();

            DrawFPS(10, 10);

        EndDrawing();
    }

    GameClose();
}

void GameClose() {
    CloseWindow();
}