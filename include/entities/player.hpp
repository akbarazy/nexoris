#pragma once
#include <raylib.h>

class Player
{
private:
    Vector2 position;
    float speed;

public:
    Player();
    void Update();
    void Draw();
};