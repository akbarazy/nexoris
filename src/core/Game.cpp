#include "core/game.hpp"
#include "raylib.h"

void Game::Run()
{
    InitWindow(1280, 720, "Nexoris");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("NEXORIS", 500, 350, 40, WHITE);
        EndDrawing();
    }

    CloseWindow();
}