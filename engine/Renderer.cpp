#include "Renderer.hpp"
#include <iostream>

bool Renderer::init(int w, int h, const std::string& title) {
    std::cout << "[Renderer] Init window " << title << " size " << w << "x" << h << " (stub)\n";
    return true;
}

void Renderer::clear() {
    // Stub: would clear screen
}

void Renderer::present() {
    // Stub: would swap buffers
}

void Renderer::drawTexture(TextureHandle tex, Vec2 pos, Vec2 size) {
    std::cout << "[Renderer] Draw texture " << tex << " at (" << pos.x << ", " << pos.y
              << ") size (" << size.x << ", " << size.y << ")\n";
}

void Renderer::drawText(const std::string& text, Vec2 pos, float fontSize) {
    std::cout << "[Renderer] Draw text '" << text << "' at (" << pos.x << ", " << pos.y
              << ") size " << fontSize << "\n";
}

void Renderer::shutdown() {
    std::cout << "[Renderer] Shutdown\n";
}
