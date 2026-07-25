#pragma once
#include "ReelManager.hpp"
#include "StateManager.hpp"
#include "SDL3_mixer/SDL_mixer.h"

class AudioManager{
private:
    MIX_Mixer* mixer;

    MIX_Audio* stopReelSE;
    MIX_Audio* startReelSE;
    MIX_Audio* betSE;

    MIX_Track* stopReelTrack;
    MIX_Track* startReelTrack;
    MIX_Track* betTrack;

    MIX_Audio* RedBBBGM;
    MIX_Track* BGMTrack;

    void playSE();
    void playBGM(MIX_Audio* bgm);
    void stopBGM();

public:
    void init();
    // Sound SE
    void SE(const ReelEvent& reelEvent, const StateEvent& stateEvent);
    void BGM(const StateEvent& stateEvent);
    void exit();
};
