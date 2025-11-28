#include "Application.hpp"
#include <chrono>
#include <iostream>
#include <filesystem>

bool Application::init(const Config& cfg) {
    cfg_ = cfg;
    if (!renderer_.init(cfg.windowWidth, cfg.windowHeight, cfg.title)) return false;
    if (!audio_.init()) return false;

    const std::filesystem::path scriptRel = "scripts/main.txt";
    const std::filesystem::path scriptSourceRoot = std::filesystem::path(PROJECT_SOURCE_DIR) / scriptRel;
    const std::filesystem::path scriptRunDir = scriptRel;

    auto tryLoad = [&](const std::filesystem::path& p) {
        return script_.load(p.string());
    };

    if (!tryLoad(scriptRunDir) && !tryLoad(scriptSourceRoot)) {
        std::cerr << "Failed to load script " << scriptRel.string() << "\n"
                  << "Tried: " << std::filesystem::absolute(scriptRunDir) << "\n"
                  << "       " << std::filesystem::absolute(scriptSourceRoot) << "\n";
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
