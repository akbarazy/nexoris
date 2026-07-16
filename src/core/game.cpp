#include <raylib.h>
#include "core/game.hpp"

Game::Game() {}

Game::~Game()
{
    UnloadRenderTexture(screen.canvas);
    CloseWindow();
}

void Game::Update() {
    float dt = GetFrameTime();
}

void Game::Render() {}

void Game::Run()
{
    while (!WindowShouldClose())
    {
        if (!IsWindowFocused() && !IsWindowMinimized())
            MinimizeWindow();

        Update();

        BeginTextureMode(screen.canvas);
        ClearBackground(BLACK);

        Render();

        EndTextureMode();

        screen.Render();
    }
}