#include "game/factories/entity_factory.hpp"
#include "engine/ecs/components.hpp"

using namespace nexoris::engine::ecs;

namespace nexoris {
namespace game {

entt::entity EntityFactory::CreatePlayer(entt::registry& registry, float x, float y) {
    auto entity = registry.create();
    
    registry.emplace<Transform2D>(entity, Vector2{x, y}, Vector2{0.0f, 0.0f}, Vector2{x, y});
    registry.emplace<Renderable>(entity, BLUE, Vector2{32.0f, 32.0f});
    registry.emplace<BoxCollider>(entity, Vector2{32.0f, 32.0f}, Vector2{0.0f, 0.0f});
    registry.emplace<PlayerInput>(entity, 5.0f);
    registry.emplace<CameraTarget>(entity);
    
    return entity;
}

entt::entity EntityFactory::CreateMapObstacle(entt::registry& registry, Rectangle rect) {
    auto entity = registry.create();
    
    registry.emplace<Transform2D>(entity, Vector2{rect.x, rect.y}, Vector2{0.0f, 0.0f}, Vector2{rect.x, rect.y});
    registry.emplace<Renderable>(entity, GRAY, Vector2{rect.width, rect.height});
    registry.emplace<BoxCollider>(entity, Vector2{rect.width, rect.height}, Vector2{0.0f, 0.0f});
    registry.emplace<StaticBody>(entity);
    
    return entity;
}

entt::entity EntityFactory::CreateMapArea(entt::registry& registry, Rectangle rect) {
    auto entity = registry.create();
    
    registry.emplace<Transform2D>(entity, Vector2{rect.x, rect.y}, Vector2{0.0f, 0.0f}, Vector2{rect.x, rect.y});
    registry.emplace<Renderable>(entity, DARKGREEN, Vector2{rect.width, rect.height});
    // No collider for the background area
    
    return entity;
}

} // namespace game
} // namespace nexoris
