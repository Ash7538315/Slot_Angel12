#include "AudioManager.hpp"
#include "SDL3/SDL_audio.h"
#include "SDL3_mixer/SDL_mixer.h"


void AudioManager::playBGM(MIX_Audio* bgm){
    MIX_SetTrackAudio(BGMTrack, bgm);
    MIX_PlayTrack(BGMTrack, -1);
};

void AudioManager::stopBGM(){
    Sint64 frames = MIX_TrackMSToFrames(BGMTrack, 500); 
    MIX_StopTrack(BGMTrack, frames);
}

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
    
    stopReelSE = MIX_LoadAudio(mixer, "../asset/se/stop_reel.wav", true);
    startReelSE = MIX_LoadAudio(mixer, "../asset/se/start_reel.wav", true);
    betSE = MIX_LoadAudio(mixer, "../asset/se/bet.wav", true);

    stopReelTrack = MIX_CreateTrack(mixer);
    startReelTrack = MIX_CreateTrack(mixer);
    betTrack = MIX_CreateTrack(mixer);

    MIX_SetTrackAudio(stopReelTrack, stopReelSE);
    MIX_SetTrackAudio(startReelTrack, startReelSE);
    MIX_SetTrackAudio(betTrack, betSE);

    // RedBBBGM = MIX_LoadAudio(mixer, "../asset/bgm/Trap_Trap_Blitzkrieg_2.mp3", false);
    BGMTrack = MIX_CreateTrack(mixer);
}

void AudioManager::SE(const ReelEvent& reelEvent, const StateEvent& stateEvent){
    if (reelEvent.startReel) {
        MIX_PlayTrack(startReelTrack, 0);
    };
    if (reelEvent.stopLeftReel || reelEvent.stopCenterReel || reelEvent.stopRightReel) {
        MIX_PlayTrack(stopReelTrack, 0);
    }
    if (stateEvent.bet) {
        MIX_PlayTrack(betTrack, 0);
    }
};

void AudioManager::BGM(const StateEvent& stateEvent){
    if (stateEvent.startRedBB) {
        playBGM(RedBBBGM);
    }
    if (stateEvent.endBonus){
        stopBGM();
    }
};

void AudioManager::exit(){
}
