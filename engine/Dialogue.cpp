#include "Dialogue.hpp"
#include "Renderer.hpp"

DialogueBox::DialogueBox(Renderer& renderer) : renderer_(renderer) {}

void DialogueBox::setLine(const DialogueLine& line) {
    current_ = line;
    visibleChars_ = 0;
}

void DialogueBox::showAll() {
    visibleChars_ = current_.text.size();
}

void DialogueBox::update(float dt) {
    if (visibleChars_ < current_.text.size()) {
        visibleChars_ += static_cast<size_t>(speed_ * dt);
        if (visibleChars_ > current_.text.size()) visibleChars_ = current_.text.size();
    }
}

void DialogueBox::render() {
    std::string partial = current_.text.substr(0, visibleChars_);
    if (!current_.speaker.empty()) {
        renderer_.drawText(current_.speaker + ":", {0.05f, 0.8f}, 24.0f);
    }
    renderer_.drawText(partial, {0.05f, 0.85f}, 24.0f);
}

bool DialogueBox::isFinished() const {
    return visibleChars_ >= current_.text.size();
}
