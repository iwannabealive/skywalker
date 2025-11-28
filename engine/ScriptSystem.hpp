#pragma once
#include <functional>
#include <istream>
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
    bool loadFromString(const std::string& script, const std::string& sourceName = "<memory>");
    void reset();
    const Command* next();
    void jump(const std::string& label);

private:
    bool parseStream(std::istream& is, const std::string& sourceName);
    std::vector<Command> cmds_;
    std::unordered_map<std::string, size_t> labelMap_;
    size_t pc_ = 0;
};
