#include "systems/spawn.hpp"
#include "components/transform.hpp"
#include "components/collider.hpp"
#include "components/velocity.hpp"
#include "components/tags.hpp"
#include "components/tile.hpp"
#include "components/blocking.hpp"
#include "components/shadow.hpp"

namespace Spawn {
    void Init(entt::registry& registry) {
        for (int row = 0; row < 10; row++) {
            for (int col = 0; col < 10; col++) {
                auto tile = registry.create();
                registry.emplace<Transform2D>(tile, Vector2{(float)(col * 16), (float)(row * 16)});
                registry.emplace<Tile>(tile, TileLayer::Background);
            }
        }

        for (int row = 2; row < 8; row++) {
            for (int col = 2; col < 8; col++) {
                auto tile = registry.create();
                registry.emplace<Transform2D>(tile, Vector2{(float)(col * 16), (float)(row * 16)});
                registry.emplace<Tile>(tile, TileLayer::Floor);
            }
        }

        for (int i = 0; i < 10; i++) {
            auto wallTop = registry.create();
            registry.emplace<Transform2D>(wallTop, Vector2{(float)(i * 16), 0.0f});
            registry.emplace<Collider>(wallTop, Vector2{16.0f, 16.0f});
            registry.emplace<Tile>(wallTop, TileLayer::HalfFull);
            registry.emplace<Blocking>(wallTop, BodyType::Full, -16.0f);

            auto wallBottom = registry.create();
            registry.emplace<Transform2D>(wallBottom, Vector2{(float)(i * 16), 144.0f});
            registry.emplace<Collider>(wallBottom, Vector2{16.0f, 16.0f});
            registry.emplace<Tile>(wallBottom, TileLayer::HalfFull);
            registry.emplace<Blocking>(wallBottom, BodyType::Full, -16.0f);

            if (i > 0 && i < 9) {
                auto wallLeft = registry.create();
                registry.emplace<Transform2D>(wallLeft, Vector2{0.0f, (float)(i * 16)});
                registry.emplace<Collider>(wallLeft, Vector2{16.0f, 16.0f});
                registry.emplace<Tile>(wallLeft, TileLayer::HalfFull);
                registry.emplace<Blocking>(wallLeft, BodyType::Full, -16.0f);

                auto wallRight = registry.create();
                registry.emplace<Transform2D>(wallRight, Vector2{144.0f, (float)(i * 16)});
                registry.emplace<Collider>(wallRight, Vector2{16.0f, 16.0f});
                registry.emplace<Tile>(wallRight, TileLayer::HalfFull);
                registry.emplace<Blocking>(wallRight, BodyType::Full, -16.0f);
            }
        }

        auto block1 = registry.create();
        registry.emplace<Transform2D>(block1, Vector2{48.0f, 48.0f});
        registry.emplace<Collider>(block1, Vector2{16.0f, 16.0f});
        registry.emplace<Tile>(block1, TileLayer::HalfFull);
        registry.emplace<Blocking>(block1, BodyType::Half, -16.0f);

        auto block2 = registry.create();
        registry.emplace<Transform2D>(block2, Vector2{80.0f, 64.0f});
        registry.emplace<Collider>(block2, Vector2{16.0f, 16.0f});
        registry.emplace<Tile>(block2, TileLayer::HalfFull);
        registry.emplace<Blocking>(block2, BodyType::Half, -16.0f);

        auto player = registry.create();
        registry.emplace<Transform2D>(player, Vector2{64.0f, 64.0f});
        registry.emplace<Collider>(player, Vector2{32.0f, 32.0f});
        registry.emplace<Velocity>(player);
        registry.emplace<PlayerTag>(player);
        registry.emplace<Shadow>(player);

        auto npc = registry.create();
        registry.emplace<Transform2D>(npc, Vector2{96.0f, 80.0f});
        registry.emplace<Collider>(npc, Vector2{32.0f, 32.0f});
        registry.emplace<NpcTag>(npc);
        registry.emplace<Shadow>(npc);

        auto enemy = registry.create();
        registry.emplace<Transform2D>(enemy, Vector2{32.0f, 96.0f});
        registry.emplace<Collider>(enemy, Vector2{32.0f, 32.0f});
        registry.emplace<EnemyTag>(enemy);
        registry.emplace<Shadow>(enemy);
    }
}
