#include "engine/ecs/camera_system.hpp"
#include "engine/ecs/components.hpp"
#include <raymath.h>

namespace nexoris {
namespace engine {
namespace ecs {

CameraSystem::CameraSystem(float renderWidth, float renderHeight) {
    m_Camera = { 0 };
    m_Camera.offset = { renderWidth * 0.5f, renderHeight * 0.5f };
    m_Camera.rotation = 0.0f;
    m_Camera.zoom = 1.0f;
    
    m_FollowSpeed = 5.0f;
}

void CameraSystem::Update(entt::registry& registry, float deltaTime) {
    auto view = registry.view<Transform2D, CameraTarget>();

    for (auto entity : view) {
        const auto& transform = view.get<Transform2D>(entity);
        
        // We might want to aim at the center of the entity.
        // Assuming we also have a Renderable/BoxCollider to know its size.
        Vector2 targetPos = transform.position;
        
        if (registry.all_of<Renderable>(entity)) {
            const auto& renderable = registry.get<Renderable>(entity);
            targetPos.x += renderable.size.x * 0.5f;
            targetPos.y += renderable.size.y * 0.5f;
        }

        m_Camera.target = Vector2Lerp(m_Camera.target, targetPos, m_FollowSpeed * deltaTime);
        
        // Break early if we only want to follow one camera target
        break;
    }
}

} // namespace ecs
} // namespace engine
} // namespace nexoris
