#pragma once
#include "SDL3_mixer/SDL_mixer.h"

enum class SESound {
    StartReel,
    StopReel,
};

class AudioManager{
private:
    MIX_Mixer* mixer;

    MIX_Audio* stopReelSE;
    MIX_Audio* startReelSE;

public:
    void init();
    void playSE(const SESound& sound);
    void exit();
};
