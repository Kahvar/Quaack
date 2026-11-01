#include <stdbool.h>
#include <stdio.h>
#include <game.h>
#include <raylib.h>
#include <input.h>
#include <player/movement.h>
#include <map/map.h>
#include <map/map_loader.h>
#include <rendering/renderer.h>

// run the game with player and camera parameters
void GameRun(PlayerCamera *camera, Player *player) {
    
    // get the map location
    char name[50] = "src/core/test.map";
    // init the map
    Map map = MapInit();

    // if the map loader returns false
    if (!MapLoader(name, &map)) {
        printf("loading file failed: %s\n", name);
        MapFree(&map);
        return;
    }

    printf("map loaded: %s (%zu objects)\n", name, map.count);

    while(!WindowShouldClose()) {
        float dt = GetFrameTime();

        PlayerInput input =  CheckKeys();

        Vector3 wishDir = GetWishDir(input, camera->yaw);

        UpdateMovement(player, input, wishDir, dt);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            // update the camera with current camera and player
            UpdatePlayerCamera(camera, player);

            BeginMode3D(camera->raylib_camera);
                Renderer(&map);

                DrawGrid(10, 1.0f);
                
            EndMode3D();

            DrawText(TextFormat("Player position: x: %.2f y: %.2f z: %.2f", player->position.x, player->position.y, player->position.z), 10, 30, 20, RED);
            DrawText(TextFormat("Player speed: %.2f", player->speed), 10, 50, 20, RED);
            DrawFPS(10, 10);

        EndDrawing();
    }

    if (!MapFree(&map)) {
        printf("MapFree failed\n");
        return;
    }

    GameClose();
}

void GameClose() {
    CloseWindow();
}

