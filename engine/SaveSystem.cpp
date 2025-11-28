#include "SaveSystem.hpp"
#include <fstream>

bool SaveSystem::save(const std::string& path, const GameState& st) {
    std::ofstream ofs(path, std::ios::binary);
    if (!ofs) return false;
    size_t len = st.scriptLabel.size();
    ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
    ofs.write(st.scriptLabel.data(), len);
    ofs.write(reinterpret_cast<const char*>(&st.commandIndex), sizeof(st.commandIndex));
    return true;
}

bool SaveSystem::load(const std::string& path, GameState& st) {
    std::ifstream ifs(path, std::ios::binary);
    if (!ifs) return false;
    size_t len = 0;
    ifs.read(reinterpret_cast<char*>(&len), sizeof(len));
    st.scriptLabel.resize(len);
    ifs.read(&st.scriptLabel[0], len);
    ifs.read(reinterpret_cast<char*>(&st.commandIndex), sizeof(st.commandIndex));
    return true;
}
