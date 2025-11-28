#pragma once

struct InputState {
    bool quit = false;
    bool click = false;
    int  mouseX = 0;
    int  mouseY = 0;
};

class Input {
public:
    // In a real engine, poll OS input. Here we simulate a single click per loop.
    bool poll(InputState& state);
};
