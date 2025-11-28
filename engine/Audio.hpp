#pragma once
#include "Types.hpp"
#include <string>

class AudioSystem {
public:
    bool init();
    void playBGM(AudioHandle bgm, bool loop = true);
    void playSE(AudioHandle se);
    void stopBGM();
    void shutdown();
};
