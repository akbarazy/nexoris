#include "engine/ecs/player_control_system.hpp"
#include "engine/ecs/components.hpp"

namespace nexoris {
namespace engine {
namespace ecs {

void PlayerControlSystem::Update(entt::registry& registry, const InputManager& inputManager) {
    auto view = registry.view<Transform2D, PlayerInput>();

    for (auto entity : view) {
        auto& transform = view.get<Transform2D>(entity);
        const auto& playerInput = view.get<PlayerInput>(entity);

        transform.velocity = {0.0f, 0.0f};

        if (inputManager.IsActionDown(Action::MoveUp))    transform.velocity.y -= playerInput.speed;
        if (inputManager.IsActionDown(Action::MoveDown))  transform.velocity.y += playerInput.speed;
        if (inputManager.IsActionDown(Action::MoveLeft))  transform.velocity.x -= playerInput.speed;
        if (inputManager.IsActionDown(Action::MoveRight)) transform.velocity.x += playerInput.speed;
    }
}

} // namespace ecs
} // namespace engine
} // namespace nexoris
