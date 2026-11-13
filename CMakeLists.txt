cmake_minimum_required(VERSION 3.15)
project(Game LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(raylib 5.0 QUIET)
if(NOT raylib_FOUND)
    include(FetchContent)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 6.2
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(raylib)
endif()

find_package(OpenGL REQUIRED)

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
    src/viewmodel/gl_utils.c
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

target_link_libraries(${PROJECT_NAME} PRIVATE raylib OpenGL::GL)

if(NOT WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE m)
endif()