#include "systems/render.hpp"
#include "components/sprite.hpp"
#include "components/transform.hpp"
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
}
