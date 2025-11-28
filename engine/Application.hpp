#pragma once
#include "Audio.hpp"
#include "Config.hpp"
#include "Input.hpp"
#include "Renderer.hpp"
#include "ResourceManager.hpp"
#include "Scene.hpp"
#include "ScriptSystem.hpp"

class Application {
public:
    bool init(const Config& cfg);
    void run();
    void shutdown();

private:
    Config cfg_;
    Renderer renderer_;
    AudioSystem audio_;
    Input input_;
    ResourceManager rm_;
    ScriptSystem script_;
    Scene* scene_ = nullptr;
};
