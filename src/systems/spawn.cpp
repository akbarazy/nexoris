#include "systems/spawn.hpp"
#include "components/transform.hpp"
#include "components/collider.hpp"
#include "components/velocity.hpp"
#include "components/tags.hpp"

namespace Spawn {
    void TestScene(entt::registry& registry) {
        for (int row = 0; row < 10; row++) {
            for (int col = 0; col < 10; col++) {
                auto tile = registry.create();
                registry.emplace<Transform2D>(tile, Vector2{(float)(col * 16), (float)(row * 16)});
                registry.emplace<Collider>(tile, Vector2{16.0f, 16.0f}, Vector2{0.0f, 0.0f}, true);
            }
        }

        auto player = registry.create();
        registry.emplace<Transform2D>(player, Vector2{64.0f, 64.0f});
        registry.emplace<Collider>(player, Vector2{32.0f, 32.0f});
        registry.emplace<Velocity>(player);
        registry.emplace<PlayerTag>(player);
    }
}
