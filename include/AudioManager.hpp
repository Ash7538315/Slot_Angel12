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

    MIX_Track* stopReelTrack;
    MIX_Track* startReelTrack;

public:
    void init();
    // Sound SE
    void playSE(const SESound& sound);
    void exit();
};
