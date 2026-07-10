#include "engine/ecs/collision_system.hpp"
#include "engine/ecs/components.hpp"
#include <raylib.h>

namespace nexoris {
namespace engine {
namespace ecs {

void CollisionSystem::Update(entt::registry& registry) {
    auto dynamicView = registry.view<Transform2D, BoxCollider>(entt::exclude<StaticBody>);
    auto staticView = registry.view<Transform2D, BoxCollider, StaticBody>();

    for (auto dynamicEntity : dynamicView) {
        auto& dynTransform = dynamicView.get<Transform2D>(dynamicEntity);
        auto& dynCollider = dynamicView.get<BoxCollider>(dynamicEntity);

        if (dynTransform.velocity.x == 0.0f && dynTransform.velocity.y == 0.0f) {
            continue;
        }

        // Create player hitbox based on current position
        Rectangle dynHitbox = {
            dynTransform.position.x + dynCollider.offset.x,
            dynTransform.position.y + dynCollider.offset.y,
            dynCollider.size.x,
            dynCollider.size.y
        };

        for (auto staticEntity : staticView) {
            auto& statTransform = staticView.get<Transform2D>(staticEntity);
            auto& statCollider = staticView.get<BoxCollider>(staticEntity);

            Rectangle statHitbox = {
                statTransform.position.x + statCollider.offset.x,
                statTransform.position.y + statCollider.offset.y,
                statCollider.size.x,
                statCollider.size.y
            };

            if (CheckCollisionRecs(dynHitbox, statHitbox)) {
                // Determine collision axis based on previous position
                Rectangle prevDynHitbox = {
                    dynTransform.previousPosition.x + dynCollider.offset.x,
                    dynTransform.previousPosition.y + dynCollider.offset.y,
                    dynCollider.size.x,
                    dynCollider.size.y
                };

                // Check horizontal collision separately
                Rectangle horizontalHitbox = prevDynHitbox;
                horizontalHitbox.x = dynHitbox.x;
                
                if (CheckCollisionRecs(horizontalHitbox, statHitbox)) {
                    if (dynTransform.velocity.x > 0) {
                        dynTransform.position.x = statHitbox.x - dynCollider.size.x - dynCollider.offset.x;
                    } else if (dynTransform.velocity.x < 0) {
                        dynTransform.position.x = statHitbox.x + statHitbox.width - dynCollider.offset.x;
                    }
                    dynTransform.velocity.x = 0;
                    dynHitbox.x = dynTransform.position.x + dynCollider.offset.x;
                }

                // Check vertical collision separately
                Rectangle verticalHitbox = prevDynHitbox;
                verticalHitbox.y = dynHitbox.y;

                if (CheckCollisionRecs(verticalHitbox, statHitbox)) {
                    if (dynTransform.velocity.y > 0) {
                        dynTransform.position.y = statHitbox.y - dynCollider.size.y - dynCollider.offset.y;
                    } else if (dynTransform.velocity.y < 0) {
                        dynTransform.position.y = statHitbox.y + statHitbox.height - dynCollider.offset.y;
                    }
                    dynTransform.velocity.y = 0;
                    dynHitbox.y = dynTransform.position.y + dynCollider.offset.y;
                }
            }
        }
    }
}

} // namespace ecs
} // namespace engine
} // namespace nexoris
