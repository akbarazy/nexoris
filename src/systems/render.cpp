#include "systems/render.hpp"
#include "components/sprite.hpp"
#include "components/transform.hpp"
#include "components/collider.hpp"
#include "components/tags.hpp"
#include "core/asset.hpp"

namespace Render {
    void Draw(entt::registry& registry) {
        auto view = registry.view<Sprite, Transform2D>();

        registry.sort<Sprite>([](const auto& lhs, const auto& rhs) {
            return lhs.zIndex < rhs.zIndex;
        });

        for (auto entity : view) {
            auto& sprite = view.get<Sprite>(entity);
            auto& transform = view.get<Transform2D>(entity);

            Asset::Display display;
            display.position = transform.position;
            display.flip = sprite.flip;

            Asset::Draw(sprite.frameId, display);
        }
    }

    void DrawTestScene(entt::registry& registry) {
        auto view = registry.view<Transform2D, Collider>();

        for (auto entity : view) {
            if (!registry.all_of<PlayerTag>(entity)) {
                auto& transform = view.get<Transform2D>(entity);
                auto& collider = view.get<Collider>(entity);
                DrawRectangle(
                    (int)transform.position.x,
                    (int)transform.position.y,
                    (int)collider.size.x,
                    (int)collider.size.y,
                    GREEN
                );
            }
        }
        
        for (auto entity : view) {
            if (registry.all_of<PlayerTag>(entity)) {
                auto& transform = view.get<Transform2D>(entity);
                auto& collider = view.get<Collider>(entity);
                DrawRectangle(
                    (int)transform.position.x,
                    (int)transform.position.y,
                    (int)collider.size.x,
                    (int)collider.size.y,
                    BLUE
                );
            }
        }
    }
}
