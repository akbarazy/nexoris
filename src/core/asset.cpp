#include <raylib.h>
#include "core/asset.hpp"

using namespace entt::literals;

Texture2D Asset::textures[Asset::MAX_TEXTURES] = {0};
std::unordered_map<entt::id_type, Asset::Frame> Asset::loadedFrames;

void Asset::Init() {
    Load(TILESET_MAPS_1, "assets/textures/tiles/maps_1.png");
    Load(SPRITESHEET_PLAYER_1, "assets/textures/sprites/player_1.png");
    Load(SPRITESHEET_EFFECTS_1, "assets/textures/sprites/effects_1.png");
    
    Register();
}

void Asset::Close() {
    for (int i = 0; i < MAX_TEXTURES; i++) {
        if (textures[i].id != 0) {
            UnloadTexture(textures[i]);
            textures[i] = {0};
        }
    }
}

void Asset::Load(Slot slot, const char* path) {
    Image img = LoadImage(path);
    textures[slot] = LoadTextureFromImage(img);
    UnloadImage(img);
}

void Asset::Register() {
    loadedFrames["gate_ceil_1"_hs] = { TILESET_MAPS_1, 0, 0, 1, 1, FRAME_16 };
    loadedFrames["gate_half_1"_hs]  = { TILESET_MAPS_1, 1, 0, 1, 1, FRAME_16 };
    loadedFrames["gate_full_1"_hs]  = { TILESET_MAPS_1, 2, 0, 1, 1, FRAME_16 };
    loadedFrames["woodenWall_full_1"_hs]  = { TILESET_MAPS_1, 3, 0, 1, 1, FRAME_16 };
    loadedFrames["woodenWall_ceil_1"_hs]  = { TILESET_MAPS_1, 4, 0, 1, 1, FRAME_16 };
    loadedFrames["mapName_floor_1"_hs]  = { TILESET_MAPS_1, 5, 0, 1, 1, FRAME_16 };
    loadedFrames["mapName_floor_2"_hs]  = { TILESET_MAPS_1, 6, 0, 1, 1, FRAME_16 };
    loadedFrames["mapName_background"_hs]  = { TILESET_MAPS_1, 7, 0, 1, 1, FRAME_16 };
    loadedFrames["mapName_floor_3"_hs]  = { TILESET_MAPS_1, 8, 0, 1, 1, FRAME_16 };
    loadedFrames["mapName_floor_4"_hs]  = { TILESET_MAPS_1, 9, 0, 1, 1, FRAME_16 };
    loadedFrames["commonChest_full"_hs]  = { TILESET_MAPS_1, 0, 1, 1, 1, FRAME_16 };
    loadedFrames["commonChestClosed_ceil"_hs]  = { TILESET_MAPS_1, 1, 1, 1, 1, FRAME_16 };
    loadedFrames["commonChestOpen_ceil"_hs]  = { TILESET_MAPS_1, 2, 1, 1, 1, FRAME_16 };
    loadedFrames["stoneBlock_full_1"_hs]  = { TILESET_MAPS_1, 3, 1, 1, 1, FRAME_16 };
    loadedFrames["stoneBlock_ceil_2"_hs]  = { TILESET_MAPS_1, 4, 1, 1, 1, FRAME_16 };

    loadedFrames["male_unarmed_idle_1"_hs]  = { SPRITESHEET_PLAYER_1, 0, 0, 1, 1, FRAME_32 };
    loadedFrames["male_unarmed_idle_2"_hs]  = { SPRITESHEET_PLAYER_1, 1, 0, 1, 1, FRAME_32 };
    loadedFrames["playerShadow"_hs]  = { SPRITESHEET_EFFECTS_1, 0, 0, 1, 1, FRAME_32 };
    loadedFrames["enemyShadow"_hs]  = { SPRITESHEET_EFFECTS_1, 1, 0, 1, 1, FRAME_32 };
    loadedFrames["npcShadow"_hs]  = { SPRITESHEET_EFFECTS_1, 2, 0, 1, 1, FRAME_32 };
}

const Asset::Frame& Asset::Get(entt::id_type id) {
    auto it = loadedFrames.find(id);
    if (it != loadedFrames.end()) {
        return it->second;
    }

    static const Frame fallback = { TILESET_MAPS_1, 0, 0, 1, 1, FRAME_16 };
    return fallback;
}

void Asset::Draw(entt::id_type id, const Display& display) {
    const Frame& frame = Get(id);

    Rectangle src = {
        (float)(frame.positionX * (frame.size + FRAME_GAP)),
        (float)(frame.positionY * (frame.size + FRAME_GAP)),
        (float)(frame.width * frame.size),
        (float)(frame.height * frame.size)
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