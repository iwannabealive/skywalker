#pragma once
#include "Types.hpp"
#include <string>
#include <unordered_map>

class ResourceManager {
public:
    TextureHandle loadTexture(const std::string& path);
    AudioHandle   loadAudio(const std::string& path);
    void unloadAll();

private:
    std::unordered_map<std::string, TextureHandle> textures_;
    std::unordered_map<std::string, AudioHandle>   audios_;
    TextureHandle nextTexture_{1};
    AudioHandle nextAudio_{1};
};
