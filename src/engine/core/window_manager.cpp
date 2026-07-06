#include "engine/core/window_manager.hpp"
#include <algorithm>

namespace nexoris {
namespace engine {

WindowManager::WindowManager() {
}

WindowManager::~WindowManager() {
    Close();
}

void WindowManager::Init(const std::string& title) {
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(GAME_WIDTH, GAME_HEIGHT, title.c_str());
    
    int monitor = GetCurrentMonitor();
    SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
    SetWindowPosition(0, 0);

    SetTargetFPS(60);

    m_Canvas = LoadRenderTexture(RENDER_WIDTH, RENDER_HEIGHT);
    SetTextureFilter(m_Canvas.texture, TEXTURE_FILTER_POINT);
}

void WindowManager::Close() {
    if (IsWindowReady()) {
        UnloadRenderTexture(m_Canvas);
        CloseWindow();
    }
}

void WindowManager::Update() {
    if (!IsWindowFocused() && !IsWindowMinimized()) {
        MinimizeWindow();
    }
}

void WindowManager::BeginRender() {
    BeginTextureMode(m_Canvas);
    ClearBackground(BLACK);
}

void WindowManager::EndRender() {
    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);

    float scale = std::min(
        (float)GetScreenWidth() / GAME_WIDTH, 
        (float)GetScreenHeight() / GAME_HEIGHT
    );
    
    Rectangle source = { 
        (RENDER_WIDTH - GAME_WIDTH) * 0.5f, 
        (RENDER_HEIGHT - GAME_HEIGHT) * 0.5f, 
        (float)GAME_WIDTH, 
        (float)-GAME_HEIGHT 
    };

    Rectangle dest = { 
        (GetScreenWidth() - ((float)GAME_WIDTH * scale)) * 0.5f,
        (GetScreenHeight() - ((float)GAME_HEIGHT * scale)) * 0.5f,
        (float)GAME_WIDTH * scale, 
        (float)GAME_HEIGHT * scale 
    };

    DrawTexturePro(m_Canvas.texture, source, dest, { 0.0f, 0.0f }, 0.0f, WHITE);
    EndDrawing();
}

bool WindowManager::ShouldClose() const {
    return WindowShouldClose();
}

void WindowManager::BeginCameraMode(Camera2D camera) {
    BeginMode2D(camera);
}

void WindowManager::EndCameraMode() {
    EndMode2D();
}

} // namespace engine
} // namespace nexoris
