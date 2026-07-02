#include "core/game.hpp"
#include "raylib.h"
#include <algorithm>

Game::Game()
{
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(GAME_WIDTH, GAME_HEIGHT, "Nexoris");
    
    // mengatur ukuran jendela agar sesuai dengan resolusi monitor
    int monitor = GetCurrentMonitor();
    SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
    SetWindowPosition(0, 0);

    SetTargetFPS(60);

    // membuat canvas supaya resolusi game tidak berubah saat resolusi monitor berubah
    canvas = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);
    SetTextureFilter(canvas.texture, TEXTURE_FILTER_POINT);
}

Game::~Game()
{
    UnloadRenderTexture(canvas);
    CloseWindow();
}

void Game::Update()
{
    player.Update(map);
}

void Game::Draw()
{
    map.Draw();
    player.Draw();
}

void Game::Render()
{
    // menggambar canvas ke layar
    BeginDrawing();
    ClearBackground(BLACK);

    float scale = std::min((float)GetScreenWidth() / GAME_WIDTH, (float)GetScreenHeight() / GAME_HEIGHT);
    Rectangle source = { 0.0f, 0.0f, (float)canvas.texture.width, (float)-canvas.texture.height };

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
        // window akan minimize saat membuka window lain
        if (!IsWindowFocused() && !IsWindowMinimized())
        {
            MinimizeWindow();
        }

        Update();

        // menggambar texture ke canvas
        BeginTextureMode(canvas);
        ClearBackground(BLACK);

        Draw();

        EndTextureMode();

        Render();
    }
}