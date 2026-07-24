#include <iostream>
#include "AudioManager.hpp"
#include "FlagManager.hpp"
#include "ReelManager.hpp"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_timer.h"
#include "InputManager.hpp"
#include "Game.hpp"

using namespace std;

void Game::init(){
    flagManager.init();
    renderer.init();
    reelManager.init();
    audioManager.init();
};

void Game::run(){
    running = true;
    Uint64 prev = SDL_GetPerformanceCounter();
    Uint64 now = SDL_GetPerformanceCounter();
    double freq = SDL_GetPerformanceFrequency();
    double accum = 0.00;
    double dt;

    // Title
    renderer.title();
    while (true) {
        // Detect inputs
        inputManager.clear();
        inputManager.check();
        if (inputManager.state().lever == true){break;}
        else if (inputManager.state().quit == true){
        running = false;
        }
    }

    while (running) {
        // Time control
        now = SDL_GetPerformanceCounter();
        dt = (now - prev) / freq;
        accum += dt;
        prev = now;

        // Detect inputs
        inputManager.check();

        // Update game;
        while (accum >= GameConst::timestep){
            accum -= GameConst::timestep;
            update();
            inputManager.clear();
        }
        renderer.reelUpdate(reelManager.leftReel.reelPos, reelManager.centerReel.reelPos, reelManager.rightReel.reelPos);
    }
};

void Game::exit(){
    renderer.exit();
    audioManager.exit();
};

void Game::update(){
    // Exit game
    if(inputManager.state().quit == true){
        running = false;
    }

    // lever on 
    if (inputManager.state().lever == true && reelManager.reelsState == ReelState::Stop ){
        flagManager.draw();
        cout << flagManager.currentFlag.name << endl; // debug
    }

    // reel ctrl
    reelManager.ctrl(inputManager.state(), flagManager.currentFlag.ctrl, flagManager.bonusState);

    // Start Reel
    if (reelManager.event.startReel == true) {
        audioManager.playSE(SESound::StartReel);
    }

    // Stop Reel
    if (reelManager.event.stopLeftReel == true || reelManager.event.stopCenterReel == true || reelManager.event.stopRightReel == true ) {
        audioManager.playSE(SESound::StopReel);
        
    }

};

