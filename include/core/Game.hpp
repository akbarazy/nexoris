#pragma once
#include "entities/player.hpp"
#include "world/map.hpp"

class Game
{
private:
    Player player;
    Map map;

public:
    static constexpr int GAME_WIDTH = 1280;
    static constexpr int GAME_HEIGHT = 720;

    void Run();
};