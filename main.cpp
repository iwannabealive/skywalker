#include "engine/Application.hpp"
#include "engine/Config.hpp"
#include <iostream>

int main(int argc, char** argv) {
    Config cfg;
    Application app;
    const char* exePath = (argc > 0 && argv[0]) ? argv[0] : "";
    if (!app.init(cfg, exePath)) {
        std::cerr << "Initialization failed" << std::endl;
        return -1;
    }
    app.run();
    app.shutdown();
    return 0;
}
