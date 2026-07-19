#include <raylib.h>
#include "core/game.hpp"
#include "systems/render.hpp"

Game::Game() {
    Asset::Init();
}

Game::~Game()
{
    Asset::Close();
}

void Game::Run()
{
    while (!WindowShouldClose())
    {
        if (!IsWindowFocused() && !IsWindowMinimized())
            MinimizeWindow();

        Update();

        BeginTextureMode(screen.canvas);
        ClearBackground(BLACK);

        Draw();

        EndTextureMode();

        screen.Draw();
    }
}

void Game::Update() {
    float dt = GetFrameTime();
}

void Game::Draw() {
    Render::Draw(registry);
}