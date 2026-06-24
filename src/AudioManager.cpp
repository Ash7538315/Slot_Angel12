#include "AudioManager.hpp"
#include "SDL3/SDL_audio.h"
#include "SDL3_mixer/SDL_mixer.h"

void AudioManager::init(){
    bool ok = SDL_Init(SDL_INIT_AUDIO);
    bool mixOk = MIX_Init();

    SDL_Log("mixOk=%d", mixOk);

    SDL_AudioSpec spec{};
    spec.freq = 48000;
    spec.format = SDL_AUDIO_S16;
    spec.channels = 2;

    mixer = MIX_CreateMixerDevice(
        SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,
        &spec
    );

    SDL_Log("mixer=%p", mixer);
    SDL_Log("error=%s", SDL_GetError());
    
    stopReelSE = MIX_LoadAudio(mixer, "../asset/audio/se/stop_reel.wav", true);
    startReelSE = MIX_LoadAudio(mixer, "../asset/audio/se/start_reel.wav", true);
}

void AudioManager::playSE(const SESound& sound){
    switch (sound) {
        case SESound::StartReel:
            MIX_PlayAudio(mixer, startReelSE);
            return;
        case SESound::StopReel:
            MIX_PlayAudio(mixer, stopReelSE);
            return;
        default:
            return;
    }
};

void AudioManager::exit(){}
