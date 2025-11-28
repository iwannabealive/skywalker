#include "Audio.hpp"
#include <iostream>

bool AudioSystem::init() {
    std::cout << "[Audio] Init (stub)\n";
    return true;
}

void AudioSystem::playBGM(AudioHandle bgm, bool loop) {
    std::cout << "[Audio] Play BGM " << bgm << " loop=" << std::boolalpha << loop << "\n";
}

void AudioSystem::playSE(AudioHandle se) {
    std::cout << "[Audio] Play SE " << se << "\n";
}

void AudioSystem::stopBGM() {
    std::cout << "[Audio] Stop BGM\n";
}

void AudioSystem::shutdown() {
    std::cout << "[Audio] Shutdown\n";
}
