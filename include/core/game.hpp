#pragma once
#include "entities/player.hpp"
#include "world/map.hpp"

class Game
{
private:
    RenderTexture2D canvas;
    Camera2D camera;
    Player player;
    Map map;

    void Update();
    void Draw();
    void Render();

public:
    static constexpr int GAME_WIDTH = 1280;
    static constexpr int GAME_HEIGHT = 720;
    static constexpr int RENDER_WIDTH = 1920;
    static constexpr int RENDER_HEIGHT = 1080;

    Game();
    ~Game();
    void Run();
};