#include "Application.hpp"
#include <chrono>
#include <iostream>
#include <filesystem>
#include <vector>

bool Application::init(const Config& cfg, const std::filesystem::path& exePath) {
    cfg_ = cfg;
    if (!renderer_.init(cfg.windowWidth, cfg.windowHeight, cfg.title)) return false;
    if (!audio_.init()) return false;

    const std::filesystem::path scriptRel = "scripts/main.txt";
    const std::filesystem::path scriptSourceRoot = std::filesystem::path(PROJECT_SOURCE_DIR) / scriptRel;

    std::vector<std::filesystem::path> candidates;
    candidates.push_back(scriptRel); // working directory

    if (!exePath.empty()) {
        std::error_code ec;
        auto exeCanonical = std::filesystem::weakly_canonical(exePath, ec);
        if (!ec) {
            auto exeDir = exeCanonical.parent_path();
            if (!exeDir.empty()) {
                candidates.push_back(exeDir / scriptRel);
            }
        }
    }

    candidates.push_back(scriptSourceRoot);

    std::filesystem::path loadedPath;
    for (const auto& p : candidates) {
        if (script_.load(p.string())) {
            loadedPath = p;
            break;
        }
    }

    if (loadedPath.empty()) {
        std::cerr << "Failed to load script " << scriptRel.string() << "\n";
        for (const auto& p : candidates) {
            std::cerr << "Tried: " << std::filesystem::absolute(p) << "\n";
        }
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
