#include "engine/ecs/movement_system.hpp"
#include "engine/ecs/components.hpp"

namespace nexoris {
namespace engine {
namespace ecs {

void MovementSystem::Update(entt::registry& registry) {
    auto view = registry.view<Transform2D>();

    for (auto entity : view) {
        auto& transform = view.get<Transform2D>(entity);
        
        // Save previous position before moving
        transform.previousPosition = transform.position;
        
        if (transform.velocity.x != 0.0f || transform.velocity.y != 0.0f) {
            transform.position.x += transform.velocity.x;
            transform.position.y += transform.velocity.y;
        }
    }
}

} // namespace ecs
} // namespace engine
} // namespace nexoris
