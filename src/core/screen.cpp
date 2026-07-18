#include <raylib.h>
#include <algorithm>
#include "core/screen.hpp"

Screen::Screen() {
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(CANVAS_WIDTH, CANVAS_HEIGHT, "Nexoris");
    
    int monitor = GetCurrentMonitor();
    SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
    SetWindowPosition(0, 0);

    SetTargetFPS(60);

    canvas = LoadRenderTexture(CANVAS_WIDTH, CANVAS_HEIGHT);
    SetTextureFilter(canvas.texture, TEXTURE_FILTER_POINT);
}

void Screen::Render() {
    BeginDrawing();
    ClearBackground(BLACK);

    float scale = std::min((float)GetScreenWidth() / CANVAS_WIDTH, (float)GetScreenHeight() / CANVAS_HEIGHT);
    Rectangle source = { 0.0f, 0.0f, (float)canvas.texture.width, (float)-canvas.texture.height };

    Rectangle dest = { 
        (GetScreenWidth() - ((float)CANVAS_WIDTH * scale)) * 0.5f,
        (GetScreenHeight() - ((float)CANVAS_HEIGHT * scale)) * 0.5f,
        (float)CANVAS_WIDTH * scale, 
        (float)CANVAS_HEIGHT * scale 
    };

    DrawTexturePro(canvas.texture, source, dest, { 0.0f, 0.0f }, 0.0f, WHITE);

    EndDrawing();
}

Screen::~Screen() {
    UnloadRenderTexture(canvas);
    CloseWindow();
}