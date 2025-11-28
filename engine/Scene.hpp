#pragma once
#include "Character.hpp"
#include "Dialogue.hpp"
#include "ResourceManager.hpp"
#include "Renderer.hpp"
#include "Audio.hpp"
#include "ScriptSystem.hpp"
#include <vector>

class Scene {
public:
    Scene(ResourceManager& rm, Renderer& r, AudioSystem& a, ScriptSystem& s);

    void update(float dt);
    void render();
    void onClick();

private:
    ResourceManager& rm_;
    Renderer& renderer_;
    AudioSystem& audio_;
    ScriptSystem& script_;
    DialogueBox dialog_;

    TextureHandle bgTex_ = -1;
    std::vector<Character> chars_;
    bool waitingChoice_ = false;
    std::vector<std::pair<std::string, std::string>> choices_;
};
