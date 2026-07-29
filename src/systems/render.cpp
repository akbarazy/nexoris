#include "systems/render.hpp"
#include "components/sprite.hpp"
#include "components/transform.hpp"
#include "components/collider.hpp"
#include "components/tags.hpp"
#include "components/tile.hpp"
#include "components/blocking.hpp"
#include "components/shadow.hpp"
#include "core/asset.hpp"
#include <vector>
#include <algorithm>
#include <unordered_map>

namespace Render {
    struct RenderEntry {
        float drawX;
        float drawY;
        float sortY;
        float width;
        float height;
        Color color;
        int zIndex;
        bool isCeil;
        entt::entity owner;
    };

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

    void DrawPrototype(entt::registry& registry) {
        std::vector<RenderEntry> entries;
        std::unordered_map<entt::entity, int> entityZIndex;

        auto tileView = registry.view<Transform2D, Tile>();
        for (auto entity : tileView) {
            auto& transform = tileView.get<Transform2D>(entity);
            auto& tile = tileView.get<Tile>(entity);
            
            float width = 16.0f;
            float height = 16.0f;
            if (registry.all_of<Collider>(entity)) {
                width = registry.get<Collider>(entity).size.x;
                height = registry.get<Collider>(entity).size.y;
            }

            if (tile.layer == TileLayer::Background) {
                entries.push_back({transform.position.x, transform.position.y, 0, width, height, ORANGE, 0, false, entity});
            } else if (tile.layer == TileLayer::Floor) {
                entries.push_back({transform.position.x, transform.position.y, 0, width, height, YELLOW, 1, false, entity});
            } else if (tile.layer == TileLayer::HalfFull) {
                if (registry.all_of<Blocking>(entity)) {
                    auto& blocking = registry.get<Blocking>(entity);

                    float bodyDrawY = transform.position.y;
                    float bodyHeight = height;
                    float ceilDrawY = transform.position.y + blocking.ceilOffsetY;

                    if (blocking.bodyType == BodyType::Half) {
                        bodyDrawY = transform.position.y + 8.0f;
                        bodyHeight = 8.0f;
                        ceilDrawY = transform.position.y + blocking.ceilOffsetY + 8.0f;
                    }

                    entries.push_back({transform.position.x, bodyDrawY, 0, width, bodyHeight, DARKPURPLE, 2, false, entity});

                    entries.push_back({
                        transform.position.x, 
                        ceilDrawY, 
                        transform.position.y, 
                        width, height, 
                        PURPLE, -1, true, entity
                    });
                } else {
                    entries.push_back({transform.position.x, transform.position.y, 0, width, height, DARKPURPLE, 2, false, entity});
                }
            }
        }

        auto spriteView = registry.view<Transform2D, Collider>();
        for (auto entity : spriteView) {
            if (registry.all_of<Tile>(entity)) continue;

            auto& transform = spriteView.get<Transform2D>(entity);
            auto& collider = spriteView.get<Collider>(entity);
            
            Color color = WHITE;
            if (registry.all_of<PlayerTag>(entity)) color = GREEN;
            else if (registry.all_of<NpcTag>(entity)) color = BLUE;
            else if (registry.all_of<EnemyTag>(entity)) color = RED;
            else continue;

            entries.push_back({transform.position.x, transform.position.y, transform.position.y, collider.size.x, collider.size.y, color, -1, false, entity});
            
            if (registry.all_of<Shadow>(entity)) {
                entries.push_back({transform.position.x, transform.position.y, transform.position.y, collider.size.x, collider.size.y, Fade(BLACK, 0.5f), -2, false, entity});
            }
        }

        std::vector<RenderEntry*> dynamicEntries;
        for (auto& entry : entries) {
            if (entry.zIndex == -1) {
                dynamicEntries.push_back(&entry);
            }
        }

        std::stable_sort(dynamicEntries.begin(), dynamicEntries.end(), [](const RenderEntry* a, const RenderEntry* b) {
            if (a->sortY != b->sortY) return a->sortY < b->sortY;
            return a->isCeil && !b->isCeil;
        });

        int currentZ = 3;
        for (auto* entry : dynamicEntries) {
            entry->zIndex = currentZ++;
            if (!entry->isCeil) {
                entityZIndex[entry->owner] = entry->zIndex; 
            }
        }

        for (auto& entry : entries) {
            if (entry.zIndex == -2) {
                entry.zIndex = entityZIndex[entry.owner] - 1;
            }
        }

        std::stable_sort(entries.begin(), entries.end(), [](const RenderEntry& a, const RenderEntry& b) {
            return a.zIndex < b.zIndex;
        });

        for (const auto& entry : entries) {
            DrawRectangle(
                (int)entry.drawX,
                (int)entry.drawY,
                (int)entry.width,
                (int)entry.height,
                entry.color
            );
        }
    }
}
