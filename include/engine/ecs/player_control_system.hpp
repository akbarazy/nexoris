#pragma once
#include <entt/entt.hpp>
#include "engine/core/input_manager.hpp"

namespace nexoris {
namespace engine {
namespace ecs {

class PlayerControlSystem {
public:
    void Update(entt::registry& registry, const InputManager& inputManager);
};

} // namespace ecs
} // namespace engine
} // namespace nexoris
