#include "ResourceManager.hpp"
#include <iostream>

TextureHandle ResourceManager::loadTexture(const std::string& path) {
    auto it = textures_.find(path);
    if (it != textures_.end()) return it->second;
    TextureHandle handle = nextTexture_++;
    textures_[path] = handle;
    std::cout << "[ResourceManager] Loaded texture: " << path << " -> " << handle << "\n";
    return handle;
}

AudioHandle ResourceManager::loadAudio(const std::string& path) {
    auto it = audios_.find(path);
    if (it != audios_.end()) return it->second;
    AudioHandle handle = nextAudio_++;
    audios_[path] = handle;
    std::cout << "[ResourceManager] Loaded audio: " << path << " -> " << handle << "\n";
    return handle;
}

void ResourceManager::unloadAll() {
    std::cout << "[ResourceManager] Unloading all resources" << "\n";
    textures_.clear();
    audios_.clear();
}
