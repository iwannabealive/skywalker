#include "Input.hpp"
#include <iostream>
#include <string>

bool Input::poll(InputState& state) {
    // Simple CLI-driven loop: wait for user to press Enter, 'q' to quit, 'c' to click
    std::cout << "Press Enter to advance, 'c'+Enter to click, 'q'+Enter to quit: ";
    std::string line;
    if (!std::getline(std::cin, line)) {
        state.quit = true;
        return false;
    }
    state.click = (line == "c" || line.empty());
    state.quit = (line == "q");
    return !state.quit;
}
