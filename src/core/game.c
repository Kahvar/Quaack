#include <game.h>
#include <raylib.h>
#include <input.h>
#include <player/movement.h>

// run the game with player and camera parameters
void GameRun(PlayerCamera *camera, Player *player) {
    
    Vector3 cubePosition = { 5.0f, 0.0f, 5.0f };

    while(!WindowShouldClose()) {
        float dt = GetFrameTime();

        PlayerInput input =  CheckKeys();

        Vector3 wishDir = GetWishDir(input, camera->yaw);

        UpdateMovement(player, wishDir, dt);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            // update the camera with current camera and player
            UpdatePlayerCamera(camera, player);

            BeginMode3D(camera->raylib_camera);
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

