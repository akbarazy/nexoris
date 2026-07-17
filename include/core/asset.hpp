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
        int sourceSize = SPRITE_SIZE;
    };

    struct Display {
        Vector2 position;
        int size = SPRITE_SIZE;
        Vector2 offset = {0, 0};
        Vector2 origin = {0, 0};
        float rotation = 0.0f;
        Color tint = WHITE;
        bool flip = false;
    };

    static constexpr int SPRITE_SIZE = 32;
    static constexpr int TILE_SIZE = 16;
    static constexpr int FRAME_GAP = 4;
    static constexpr int MAX_TEXTURES = 8;

    static void Init();
    static void Close();
    static const Frame& GetFrame(entt::id_type id);
    static void DrawFrame(const Frame& frame, const Display& display);
    static void DrawFrame(entt::id_type id, const Display& display);

private:
    static Texture2D textures[MAX_TEXTURES];
    static std::unordered_map<entt::id_type, Frame> loadedFrames;

    static void LoadTexture(Slot slot, const char* path);
    static void RegisterFrames();
};