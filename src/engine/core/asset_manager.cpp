#include "engine/core/asset_manager.hpp"
#include <iostream>

namespace nexoris {
namespace engine {

AssetManager::~AssetManager() {
    Clear();
}

Texture2D* AssetManager::LoadTexture(const std::string& name, const std::string& filepath) {
    if (m_Textures.find(name) != m_Textures.end()) {
        return &m_Textures[name];
    }

    Texture2D texture = ::LoadTexture(filepath.c_str());
    if (texture.id == 0) {
        std::cerr << "AssetManager: Failed to load texture at " << filepath << std::endl;
        return nullptr;
    }

    m_Textures[name] = texture;
    return &m_Textures[name];
}

Texture2D* AssetManager::GetTexture(const std::string& name) {
    auto it = m_Textures.find(name);
    if (it != m_Textures.end()) {
        return &it->second;
    }
    std::cerr << "AssetManager: Texture not found - " << name << std::endl;
    return nullptr;
}

void AssetManager::UnloadTexture(const std::string& name) {
    auto it = m_Textures.find(name);
    if (it != m_Textures.end()) {
        ::UnloadTexture(it->second);
        m_Textures.erase(it);
    }
}

void AssetManager::Clear() {
    for (auto& pair : m_Textures) {
        ::UnloadTexture(pair.second);
    }
    m_Textures.clear();
}

} // namespace engine
} // namespace nexoris
