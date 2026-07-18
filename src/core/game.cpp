#include <raylib.h>
#include "core/game.hpp"
#include "systems/render_system.hpp"

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

        Render();

        EndTextureMode();

        screen.Render();
    }
}

void Game::Update() {
    float dt = GetFrameTime();
}

void Game::Render() {
    RenderSystem::Draw(registry);
}