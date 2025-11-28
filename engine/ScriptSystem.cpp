#include "ScriptSystem.hpp"
#include <fstream>
#include <iomanip>   // for std::quoted
#include <sstream>

bool ScriptSystem::load(const std::string& scriptPath) {
    cmds_.clear();
    labelMap_.clear();
    pc_ = 0;

    std::ifstream ifs(scriptPath);
    if (!ifs) return false;

    std::string line;
    while (std::getline(ifs, line)) {
        std::istringstream iss(line);
        std::string op;
        if (!(iss >> op)) continue;

        Command cmd{};
        if (op == "say") cmd.op = OpCode::Say;
        else if (op == "bg") cmd.op = OpCode::Bg;
        else if (op == "bgm") cmd.op = OpCode::Bgm;
        else if (op == "choice") cmd.op = OpCode::Choice;
        else if (op == "jump") cmd.op = OpCode::Jump;
        else if (op == "label") cmd.op = OpCode::Label;
        else if (op == "end") { cmd.op = OpCode::End; cmds_.push_back(cmd); break; }
        else continue;

        std::string arg;
        while (iss >> std::quoted(arg)) {
            cmd.args.push_back(arg);
        }

        if (cmd.op == OpCode::Label && !cmd.args.empty()) {
            labelMap_[cmd.args[0]] = cmds_.size();
        }
        cmds_.push_back(cmd);
    }
    return true;
}

void ScriptSystem::reset() {
    pc_ = 0;
}

const Command* ScriptSystem::next() {
    if (pc_ >= cmds_.size()) return nullptr;
    return &cmds_[pc_++];
}

void ScriptSystem::jump(const std::string& label) {
    auto it = labelMap_.find(label);
    if (it != labelMap_.end()) {
        pc_ = it->second;
    }
}
