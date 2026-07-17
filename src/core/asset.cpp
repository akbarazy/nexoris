#include <raylib.h>
#include "core/asset.hpp"

using namespace entt::literals;

Texture2D Asset::textures[Asset::MAX_TEXTURES] = {0};
std::unordered_map<entt::id_type, Asset::Frame> Asset::loadedFrames;

void Asset::Init() {
    LoadTexture(TILESET_MAPS_1, "assets/textures/tiles/maps_1.png");
    LoadTexture(SPRITESHEET_PLAYER_1, "assets/textures/sprites/player_1.png");
    LoadTexture(SPRITESHEET_EFFECTS_1, "assets/textures/sprites/effects_1.png");
    
    RegisterFrames();
}

void Asset::Close() {
    for (int i = 0; i < MAX_TEXTURES; i++) {
        if (textures[i].id != 0) {
            UnloadTexture(textures[i]);
            textures[i] = {0};
        }
    }
}

void Asset::LoadTexture(Slot slot, const char* path) {
    Image img = LoadImage(path);
    textures[slot] = LoadTextureFromImage(img);
    UnloadImage(img);
}

void Asset::RegisterFrames() {
    loadedFrames["tile_grass"_hs] = { TILESET_MAPS_1, 0, 0, 1, 1, TILE_SIZE };
    loadedFrames["tile_dirt"_hs]  = { TILESET_MAPS_1, 1, 0, 1, 1, TILE_SIZE };
    
    loadedFrames["player_idle_1"_hs] = { SPRITESHEET_PLAYER_1, 0, 0, 1, 1, SPRITE_SIZE };
    loadedFrames["player_idle_2"_hs] = { SPRITESHEET_PLAYER_1, 1, 0, 1, 1, SPRITE_SIZE };
    
    loadedFrames["effect_explosion"_hs] = { SPRITESHEET_EFFECTS_1, 0, 0, 1, 1, SPRITE_SIZE };
}

const Asset::Frame& Asset::GetFrame(entt::id_type id) {
    auto it = loadedFrames.find(id);
    if (it != loadedFrames.end()) {
        return it->second;
    }

    static const Frame fallback = { TILESET_MAPS_1, 0, 0, 1, 1, TILE_SIZE };
    return fallback;
}

void Asset::DrawFrame(const Frame& frame, const Display& display) {
    Rectangle src = {
        (float)(frame.positionX * (frame.sourceSize + FRAME_GAP)),
        (float)(frame.positionY * (frame.sourceSize + FRAME_GAP)),
        (float)(frame.width * frame.sourceSize),
        (float)(frame.height * frame.sourceSize)
    };
    
    if (display.flip) {
        src.width = -src.width;
    }
    
    Rectangle dest = {
        display.position.x + display.offset.x,
        display.position.y + display.offset.y,
        (float)(frame.width * display.size),
        (float)(frame.height * display.size)
    };
    
    DrawTexturePro(textures[frame.texture], src, dest, display.origin, display.rotation, display.tint);
}

void Asset::DrawFrame(entt::id_type id, const Display& display) {
    DrawFrame(GetFrame(id), display);
}