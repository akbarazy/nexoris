#include "entities/player.hpp"
#include "world/map.hpp"

Player::Player()
{
    speed = 5.0f;
    position = { 640.0f - 16.0f, 360.0f - 16.0f };
    hitbox = { position.x, position.y, 32.0f, 32.0f };
}

void Player::Update(Map& map)
{
    Move(map);
}

void Player::Move(Map& map)
{
    float dx = 0.0f;
    float dy = 0.0f;

    if (IsKeyDown(KEY_W)) dy -= speed;
    if (IsKeyDown(KEY_S)) dy += speed;
    if (IsKeyDown(KEY_A)) dx -= speed;
    if (IsKeyDown(KEY_D)) dx += speed;

    if (dx != 0.0f)
    {
        position.x += dx;
        hitbox.x = position.x;
        CheckCollision(map, HORIZONTAL, dx);
    }

    if (dy != 0.0f)
    {
        position.y += dy;
        hitbox.y = position.y;
        CheckCollision(map, VERTICAL, dy);
    }
}

void Player::CheckCollision(Map& map, Axis axis, float delta)
{
    for (const auto& object : map.GetObjects())
    {
        if (CheckCollisionRecs(hitbox, object))
        {
            if (axis == HORIZONTAL)
            {
                if (delta > 0.0f)
                    position.x = object.x - hitbox.width;
                else if (delta < 0.0f)
                    position.x = object.x + object.width;
                hitbox.x = position.x;
            }
            else
            {
                if (delta > 0.0f)
                    position.y = object.y - hitbox.height;
                else if (delta < 0.0f)
                    position.y = object.y + object.height;
                hitbox.y = position.y;
            }
        }
    }
}

void Player::Draw()
{
    DrawRectangleRec(hitbox, BLUE);
}

Vector2 Player::GetCenter() const
{
    return { 
        position.x + hitbox.width / 2.0f, 
        position.y + hitbox.height / 2.0f 
    };
}