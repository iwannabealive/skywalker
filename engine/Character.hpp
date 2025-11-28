#pragma once
#include "Types.hpp"
#include <string>

struct Character {
    std::string name;
    TextureHandle baseTex = -1;
    TextureHandle expressionTex = -1;
    Vec2 position{0.5f, 1.0f};
};
