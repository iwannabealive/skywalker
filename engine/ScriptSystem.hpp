#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

// Supported commands
enum class OpCode { Say, Bg, Bgm, Choice, Jump, Label, End };

struct Command {
    OpCode op;
    std::vector<std::string> args;
};

class ScriptSystem {
public:
    bool load(const std::string& scriptPath);
    void reset();
    const Command* next();
    void jump(const std::string& label);

private:
    std::vector<Command> cmds_;
    std::unordered_map<std::string, size_t> labelMap_;
    size_t pc_ = 0;
};
