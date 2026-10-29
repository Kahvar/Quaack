#include <input.h>
#include <raymath.h>


PlayerInput CheckKeys() {
    return (PlayerInput) {
        .forward = IsKeyDown(KEY_W),
        .backward = IsKeyDown(KEY_S),
        .left = IsKeyDown(KEY_A),
        .right = IsKeyDown(KEY_D),
        .jump = IsKeyDown(KEY_SPACE)
    };
}
