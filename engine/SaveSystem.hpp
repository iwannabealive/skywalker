#pragma once
#include <string>

struct GameState {
    std::string scriptLabel;
    size_t commandIndex = 0;
};

class SaveSystem {
public:
    bool save(const std::string& path, const GameState& st);
    bool load(const std::string& path, GameState& st);
};
