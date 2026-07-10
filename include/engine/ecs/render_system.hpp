#pragma once
#include <entt/entt.hpp>

namespace nexoris {
namespace engine {
namespace ecs {

class RenderSystem {
public:
    void Update(entt::registry& registry);
};

} // namespace ecs
} // namespace engine
} // namespace nexoris
