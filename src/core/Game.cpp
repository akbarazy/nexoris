#include "core/game.hpp"
#include "raylib.h"
#include <algorithm>

void Game::Run()
{
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(GAME_WIDTH, GAME_HEIGHT, "Nexoris");
    
    int monitor = GetCurrentMonitor();
    SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
    SetWindowPosition(0, 0);

    
    SetTargetFPS(60);

    RenderTexture2D target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);

    while (!WindowShouldClose())
    {
        player.Update();

        BeginTextureMode(target);
        ClearBackground(BLACK);

        map.Draw();
        player.Draw();

        EndTextureMode();

        BeginDrawing();
        ClearBackground(BLACK);

        float scale = std::min((float)GetScreenWidth() / GAME_WIDTH, (float)GetScreenHeight() / GAME_HEIGHT);
        
        Rectangle sourceRec = { 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height };
        Rectangle destRec = { 
            (GetScreenWidth() - ((float)GAME_WIDTH * scale)) * 0.5f, 
            (GetScreenHeight() - ((float)GAME_HEIGHT * scale)) * 0.5f,
            (float)GAME_WIDTH * scale, 
            (float)GAME_HEIGHT * scale 
        };

        DrawTexturePro(target.texture, sourceRec, destRec, { 0.0f, 0.0f }, 0.0f, WHITE);

        EndDrawing();
    }

    UnloadRenderTexture(target);
    CloseWindow();
}