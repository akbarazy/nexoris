#include "core/game.hpp"
#include "raylib.h"

void Game::Run()
{
    InitWindow(1280, 720, "Nexoris");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        player.Update();

        BeginDrawing();
        ClearBackground(BLACK);

        map.Draw();
        player.Draw();
        
        EndDrawing();
    }

    CloseWindow();
}