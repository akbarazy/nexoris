#pragma once

#include <raylib.h>
#include <entt/entt.hpp>
#include <unordered_map>

class Asset {
public:
    enum Slot {
        TILESET_MAPS_1,
        SPRITESHEET_PLAYER_1,
        SPRITESHEET_EFFECTS_1,
    };

    struct Frame {
        Slot texture;
        int positionX;
        int positionY;
        int width = 1;
        int height = 1;
        int size;
    };

    struct Display {
        Vector2 position;
        Vector2 offset = {0, 0};
        Vector2 origin = {0, 0};
        float rotation = 0.0f;
        Color tint = WHITE;
        bool flip = false;
        int size;
    };

    static constexpr int FRAME_32 = 32;
    static constexpr int FRAME_16 = 16;
    static constexpr int FRAME_GAP = 4;
    static constexpr int MAX_TEXTURES = 8;

    static void Init();
    static void Close();
    static const Frame& Get(entt::id_type id);
    static void Draw(entt::id_type id, const Display& display);

private:
    static Texture2D textures[MAX_TEXTURES];
    static std::unordered_map<entt::id_type, Frame> loadedFrames;

    static void Load(Slot slot, const char* path);
    static void Register();
};