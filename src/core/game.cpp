#include "core/game.hpp"
#include "raylib.h"
#include <algorithm>

Game::Game() : gameCamera(RENDER_WIDTH, RENDER_HEIGHT)
{
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(GAME_WIDTH, GAME_HEIGHT, "Nexoris");
    
    // mengatur ukuran jendela agar sesuai dengan resolusi monitor
    int monitor = GetCurrentMonitor();
    SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
    SetWindowPosition(0, 0);

    SetTargetFPS(60);

    // membuat canvas supaya resolusi game tidak berubah disetiap resolusi monitor
    canvas = LoadRenderTexture(RENDER_WIDTH, RENDER_HEIGHT);
    SetTextureFilter(canvas.texture, TEXTURE_FILTER_POINT);

    gameCamera.SnapToTarget(player.GetCenter());
}

Game::~Game()
{
    UnloadRenderTexture(canvas);
    CloseWindow();
}

void Game::Update()
{
    player.Update(map);

    gameCamera.SetTargetPosition(player.GetCenter());

    float wheel = GetMouseWheelMove();
    if (wheel != 0)
    {
        gameCamera.AddZoom(wheel * 0.125f);
    }
    
    gameCamera.Update(GetFrameTime());
}

void Game::Draw()
{
    map.Draw();
    player.Draw();
}

// menggambar canvas ke layar
void Game::Render()
{
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

    // menghitung posisi canvas agar center dan membuat ukuran canvas menjadi contain
    Rectangle dest = { 
        (GetScreenWidth() - ((float)GAME_WIDTH * scale)) * 0.5f,
        (GetScreenHeight() - ((float)GAME_HEIGHT * scale)) * 0.5f,
        (float)GAME_WIDTH * scale, 
        (float)GAME_HEIGHT * scale 
    };

    DrawTexturePro(canvas.texture, source, dest, { 0.0f, 0.0f }, 0.0f, WHITE);

    EndDrawing();
}

void Game::Run()
{
    while (!WindowShouldClose())
    {
        if (!IsWindowFocused() && !IsWindowMinimized())
        {
            MinimizeWindow();
        }

        Update();

        // menggambar texture ke canvas
        BeginTextureMode(canvas);
        ClearBackground(BLACK);

        BeginMode2D(gameCamera.GetRaylibCamera());

        Draw();
        
        EndMode2D();
        EndTextureMode();

        Render();
    }
}