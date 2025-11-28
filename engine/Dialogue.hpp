#pragma once
#include <string>

class Renderer;

struct DialogueLine {
    std::string speaker;
    std::string text;
};

class DialogueBox {
public:
    explicit DialogueBox(Renderer& renderer);
    void setLine(const DialogueLine& line);
    void showAll();
    void update(float dt);
    void render();
    bool isFinished() const;

private:
    Renderer& renderer_;
    DialogueLine current_;
    size_t visibleChars_ = 0;
    float  speed_ = 40.0f; // characters per second
};
