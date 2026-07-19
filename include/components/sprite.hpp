#pragma once

#include <entt/entt.hpp>

struct Sprite {
    entt::id_type frameId;
    bool flip = false;
    int zIndex = 0;
};