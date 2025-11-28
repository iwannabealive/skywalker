#include "engine/Application.hpp"
#include "engine/Config.hpp"
#include <iostream>

int main() {
    Config cfg;
    Application app;
    if (!app.init(cfg)) {
        std::cerr << "Initialization failed" << std::endl;
        return -1;
    }
    app.run();
    app.shutdown();
    return 0;
}
