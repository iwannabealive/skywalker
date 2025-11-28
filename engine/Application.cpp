#include "Application.hpp"
#include <chrono>
#include <iostream>

bool Application::init(const Config& cfg) {
    cfg_ = cfg;
    if (!renderer_.init(cfg.windowWidth, cfg.windowHeight, cfg.title)) return false;
    if (!audio_.init()) return false;

    if (!script_.load("scripts/main.txt")) {
        std::cerr << "Failed to load script scripts/main.txt\n";
        return false;
    }

    scene_ = new Scene(rm_, renderer_, audio_, script_);
    return true;
}

void Application::run() {
    using clock = std::chrono::steady_clock;
    auto prev = clock::now();
    InputState istate;

    while (input_.poll(istate) && !istate.quit) {
        auto now = clock::now();
        float dt = std::chrono::duration<float>(now - prev).count();
        prev = now;

        if (istate.click) scene_->onClick();

        scene_->update(dt);
        renderer_.clear();
        scene_->render();
        renderer_.present();
    }
}

void Application::shutdown() {
    if (scene_) { delete scene_; scene_ = nullptr; }
    audio_.shutdown();
    renderer_.shutdown();
    rm_.unloadAll();
}
