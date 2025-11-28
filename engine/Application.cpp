#include "Application.hpp"
#include <chrono>
#include <iostream>
#include <filesystem>
#include <vector>

namespace {
// 内置脚本，确保即使缺少文件也能运行。
const char* kBuiltInScript = R"(label start
say "Alice" "你好，欢迎来到内置剧本示例。"
say "Alice" "这是为了避免脚本缺失而准备的默认内容。"
choice "去花园" "garden" "去街道" "street"
label garden
say "Alice" "花园里很安静，阳光很好。"
jump "end_label"
label street
say "Alice" "街道上有点吵，但很热闹。"
label end_label
say "Alice" "演示结束，感谢体验。"
end
)";
}

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
        std::cerr << "Failed to load script file; falling back to built-in script.\n";
        for (const auto& p : candidates) {
            std::cerr << "Tried: " << std::filesystem::absolute(p) << "\n";
        }
        if (!script_.loadFromString(kBuiltInScript, "built-in")) {
            std::cerr << "Built-in script failed to parse.\n";
            return false;
        }
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
