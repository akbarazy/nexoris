#include "world/map.hpp"

Map::Map()
{
    area = { -1000.0f, -1000.0f, 3000.0f, 3000.0f };
    objects.push_back({ 300.0f, 200.0f, 80.0f, 80.0f });
    objects.push_back({ 800.0f, 400.0f, 160.0f, 60.0f });
    objects.push_back({ 500.0f, 450.0f, 60.0f, 150.0f });
    objects.push_back({ -300.0f, -200.0f, 100.0f, 100.0f });
    objects.push_back({ 1200.0f, -150.0f, 200.0f, 80.0f });
    objects.push_back({ -500.0f, 800.0f, 80.0f, 200.0f });
    objects.push_back({ 1500.0f, 1200.0f, 300.0f, 300.0f });
    objects.push_back({ -800.0f, -800.0f, 150.0f, 150.0f });
    objects.push_back({ 800.0f, 1600.0f, 250.0f, 100.0f });
}

void Map::Draw()
{
    DrawRectangleRec(area, DARKGREEN);

    for (const auto& object : objects)
    {
        DrawRectangleRec(object, GRAY);
    }
}