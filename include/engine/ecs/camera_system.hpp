#pragma once
#include <entt/entt.hpp>
#include <raylib.h>

namespace nexoris {
namespace engine {
namespace ecs {

class CameraSystem {
public:
    CameraSystem(float renderWidth, float renderHeight);
    void Update(entt::registry& registry, float deltaTime);
    
    Camera2D GetCamera() const { return m_Camera; }

private:
    Camera2D m_Camera;
    float m_FollowSpeed;
};

} // namespace ecs
} // namespace engine
} // namespace nexoris
