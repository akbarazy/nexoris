#pragma once
#include "entities/player.hpp"
#include "world/map.hpp"

class Game
{
private:
    Player player;
    Map map;

public:
    void Run();
};