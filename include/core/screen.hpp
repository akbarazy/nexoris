#pragma once

#include <raylib.h>

class Screen {
public:
    static constexpr int CANVAS_WIDTH = 1280;
    static constexpr int CANVAS_HEIGHT = 720;
    RenderTexture2D canvas;

    Screen();
    ~Screen();
    void Draw();
};