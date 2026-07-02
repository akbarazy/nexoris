#pragma once
#include "entities/player.hpp"
#include "world/map.hpp"

class Game
{
private:
    RenderTexture2D canvas;
    Player player;
    Map map;

    void Update();
    void Draw();
    void Render();

public:
    static constexpr int GAME_WIDTH = 1280;
    static constexpr int GAME_HEIGHT = 720;

    Game();
    ~Game();
    void Run();
};