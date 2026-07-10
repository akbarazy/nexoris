#pragma once
#include <entt/entt.hpp>
#include <raylib.h>

namespace nexoris {
namespace game {

class EntityFactory {
public:
    static entt::entity CreatePlayer(entt::registry& registry, float x, float y);
    static entt::entity CreateMapObstacle(entt::registry& registry, Rectangle rect);
    static entt::entity CreateMapArea(entt::registry& registry, Rectangle rect);
};

} // namespace game
} // namespace nexoris
