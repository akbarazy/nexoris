#pragma once

#include <raylib.h>
#include <entt/entt.hpp>
#include <memory>
#include "core/screen.hpp"
#include "core/asset.hpp"

class Game {
public:
    Game();
    ~Game();
    void Run();

private:
    entt::registry registry;
    Screen screen;

    void Update();
    void Draw();
};