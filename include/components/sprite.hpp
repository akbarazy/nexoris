#pragma once

#include <raylib.h>
#include <string>

struct Sprite {
    std::string textureId;
    Rectangle srcRect = {0.0f, 0.0f, 32.0f, 32.0f};
    int zOrder = 0;
};