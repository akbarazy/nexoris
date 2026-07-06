#pragma once
#include <raylib.h>
#include <string>
#include <unordered_map>

namespace nexoris {
namespace engine {

class AssetManager {
public:
    AssetManager() = default;
    ~AssetManager();

    // Loads a texture and caches it. If already loaded, returns the cached version.
    Texture2D* LoadTexture(const std::string& name, const std::string& filepath);
    
    // Retrieves a cached texture. Returns nullptr if not found.
    Texture2D* GetTexture(const std::string& name);

    // Unload a specific texture
    void UnloadTexture(const std::string& name);

    // Unload all assets
    void Clear();

private:
    std::unordered_map<std::string, Texture2D> m_Textures;
};

} // namespace engine
} // namespace nexoris
