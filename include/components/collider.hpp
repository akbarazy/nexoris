#pragma once

#include <raylib.h>

struct Collider {
    Vector2 size = {32.0f, 32.0f};
    Vector2 offset = {0.0f, 0.0f};
    bool isSolid = true;
};