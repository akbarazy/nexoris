#include "engine/ecs/render_system.hpp"
#include "engine/ecs/components.hpp"
#include <raylib.h>

namespace nexoris {
namespace engine {
namespace ecs {

void RenderSystem::Update(entt::registry& registry) {
    auto view = registry.view<Transform2D, Renderable>();

    // Note: To implement true 2.5D Y-sorting as per ROADMAP,
    // we would sort the view by transform.position.y before drawing.
    // For Tahap 1, simple drawing is fine, but we can do a quick sort:
    registry.sort<Transform2D>([](const auto& lhs, const auto& rhs) {
        return lhs.position.y < rhs.position.y;
    });

    for (auto entity : view) {
        const auto& transform = view.get<Transform2D>(entity);
        const auto& renderable = view.get<Renderable>(entity);

        Rectangle dest = {
            transform.position.x,
            transform.position.y,
            renderable.size.x,
            renderable.size.y
        };

        DrawRectangleRec(dest, renderable.color);
    }
}

} // namespace ecs
} // namespace engine
} // namespace nexoris
