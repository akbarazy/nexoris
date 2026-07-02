#pragma once
#include <raylib.h>

class Map;

enum Axis
{
    HORIZONTAL,
    VERTICAL
};

class Player
{
private:
    Vector2 position;
    float speed;
    Rectangle hitbox;

    void Move(Map& map);
    void CheckCollision(Map& map, Axis axis, float delta);

public:
    Player();
    void Update(Map& map);
    void Draw();
};