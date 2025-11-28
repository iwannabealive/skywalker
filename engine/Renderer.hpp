#pragma once
#include "Types.hpp"
#include <string>

class Renderer {
public:
    bool init(int w, int h, const std::string& title);
    void clear();
    void present();

    void drawTexture(TextureHandle tex, Vec2 pos, Vec2 size);
    void drawText(const std::string& text, Vec2 pos, float fontSize = 24.0f);
    void shutdown();
};
