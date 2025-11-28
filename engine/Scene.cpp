#include "Scene.hpp"
#include <iostream>

Scene::Scene(ResourceManager& rm, Renderer& r, AudioSystem& a, ScriptSystem& s)
    : rm_(rm), renderer_(r), audio_(a), script_(s), dialog_(r) {}

void Scene::onClick() {
    if (!dialog_.isFinished()) {
        dialog_.showAll();
        return;
    }

    if (waitingChoice_) {
        if (!choices_.empty()) {
            std::cout << "[Scene] Auto-select choice: " << choices_[0].first << "\n";
            script_.jump(choices_[0].second);
        }
        waitingChoice_ = false;
        choices_.clear();
        return;
    }

    const Command* cmd = script_.next();
    if (!cmd) return;

    switch (cmd->op) {
    case OpCode::Say: {
        dialog_.setLine({cmd->args[0], cmd->args[1]});
        break;
    }
    case OpCode::Bg: {
        bgTex_ = rm_.loadTexture(cmd->args[0]);
        break;
    }
    case OpCode::Bgm: {
        audio_.playBGM(rm_.loadAudio(cmd->args[0]));
        break;
    }
    case OpCode::Choice: {
        choices_.clear();
        for (size_t i = 0; i + 1 < cmd->args.size(); i += 2) {
            choices_.push_back({cmd->args[i], cmd->args[i + 1]});
        }
        waitingChoice_ = true;
        std::cout << "[Scene] Choices available:" << "\n";
        for (const auto& c : choices_) {
            std::cout << " - " << c.first << " -> " << c.second << "\n";
        }
        break;
    }
    case OpCode::Jump: {
        script_.jump(cmd->args[0]);
        break;
    }
    case OpCode::Label:
    case OpCode::End:
    default:
        break;
    }
}

void Scene::update(float dt) {
    dialog_.update(dt);
}

void Scene::render() {
    if (bgTex_ >= 0) {
        renderer_.drawTexture(bgTex_, {0, 0}, {1, 1});
    }
    for (const auto& ch : chars_) {
        renderer_.drawTexture(ch.baseTex, ch.position, {0.3f, 0.6f});
    }
    dialog_.render();

    if (waitingChoice_) {
        Vec2 pos{0.05f, 0.7f};
        for (const auto& c : choices_) {
            renderer_.drawText("[choice] " + c.first, pos, 20.0f);
            pos.y += 0.05f;
        }
    }
}
