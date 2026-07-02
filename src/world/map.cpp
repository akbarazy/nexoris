#include "world/map.hpp"

Map::Map()
{
    area = { 0.0f, 0.0f, 1280.0f, 720.0f };
    objects.push_back({ 300.0f, 200.0f, 80.0f, 80.0f });
    objects.push_back({ 800.0f, 400.0f, 160.0f, 60.0f });
    objects.push_back({ 500.0f, 450.0f, 60.0f, 150.0f });
}

void Map::Draw()
{
    DrawRectangleRec(area, DARKGREEN);

    for (const auto& object : objects)
    {
        DrawRectangleRec(object, GRAY);
    }
}