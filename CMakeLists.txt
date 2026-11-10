cmake_minimum_required(VERSION 3.15)

project(Game LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)


if(WIN32)
    set(RAYLIB_DIR "C:/raylib/raylib")
endif()



add_executable(${PROJECT_NAME}
    src/main.c
    src/core/init.c
    src/core/game.c
    src/core/input.c
    src/player/camera.c
    src/player/player.c
    src/physics/movement.c
    src/physics/collision.c
    src/map/map.c
    src/map/map_loader.c
    src/rendering/renderer.c
    src/viewmodel/viewmodel.c
    
)

target_include_directories(${PROJECT_NAME} PRIVATE
    src
    src/core
    src/rendering
    src/physics
    src/player
    src/map
    src/viewmodel
)


if(WIN32)
    target_include_directories(${PROJECT_NAME} PRIVATE "${RAYLIB_DIR}/src")
    target_link_directories(${PROJECT_NAME} PRIVATE "${RAYLIB_DIR}/src")

    target_link_libraries(${PROJECT_NAME} PRIVATE
    raylib
    winmm
    gdi32
    opengl32
    )
else()
    target_link_directories(${PROJECT_NAME} PRIVATE /usr/local/lib)

    target_link_libraries(${PROJECT_NAME} PRIVATE
        raylib
        m
        pthread
        dl
        rt
        X11
    )
endif()
