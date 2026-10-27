cmake_minimum_required(VERSION 3.15)

project(Game LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    src/main.c
    src/core/init.c
    src/core/game.c
    src/player/camera.c
    src/rendering/renderer.c
    src/player/player.c
)

target_include_directories(${PROJECT_NAME} PRIVATE
    src
    src/core
    src/rendering
    src/player
)

target_link_directories(${PROJECT_NAME} PRIVATE
    /usr/local/lib
    src/core
    src/rendering
    src/player
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    raylib
    m
    pthread
    dl
    rt
    X11
)
