#include "entities/player.hpp"

Player::Player()
{
    position = {400, 225};
    speed = 5.0f;
}

void Player::Update()
{
    if (IsKeyDown(KEY_W))
        position.y -= speed;

    if (IsKeyDown(KEY_S))
        position.y += speed;

    if (IsKeyDown(KEY_A))
        position.x -= speed;

    if (IsKeyDown(KEY_D))
        position.x += speed;
}

void Player::Draw()
{
    DrawRectangle(
        position.x,
        position.y,
        32,
        32,
        BLUE
    );
}