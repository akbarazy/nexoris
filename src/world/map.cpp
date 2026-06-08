#include "world/map.hpp"

Map::Map()
{
}

void Map::Load()
{
}

void Map::Draw()
{
    DrawRectangle(
        0,
        0,
        GetScreenWidth(),
        GetScreenHeight(),
        DARKGREEN
    );
}