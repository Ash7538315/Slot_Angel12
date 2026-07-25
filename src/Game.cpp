#include <iostream>
#include "AudioManager.hpp"
#include "StateManager.hpp"
#include "ReelManager.hpp"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_timer.h"
#include "InputManager.hpp"
#include "Game.hpp"
#include "GameConst.hpp"

using namespace std;

void Game::init(){
    stateManager.init();
    renderer.init();
    reelManager.init();
    audioManager.init();
    effectManager.init();
};

void Game::run(){
    running = true;
    Uint64 prev = SDL_GetPerformanceCounter();
    Uint64 now = SDL_GetPerformanceCounter();
    double freq = SDL_GetPerformanceFrequency();
    double accum = 0.00;
    double dt;

    // Main loop
    while (running) {
        // dt control
        now = SDL_GetPerformanceCounter();
        dt = (now - prev) / freq;
        accum += dt;
        prev = now;

        // Detect inputs
        inputManager.check();

        // Update game;
        while (accum >= GameConst::timestep){
            accum -= GameConst::timestep;
            
            // Check exit
            if(inputManager.state().quit){running = false;}

            // Bet
            if (inputManager.state().bet && !stateManager.isBet) {
                stateManager.bet();
            }

            // Lever on 
            if (inputManager.state().lever && reelManager.reelsState == ReelsState::WaitLever && stateManager.isBet){
                stateManager.drawFlag();
                reelManager.reelsState = ReelsState::WaitStart;
                cout << "Draw: " <<  stateManager.currentFlag.name << endl; // debug
            }

            // Update Reel
            reelManager.update(inputManager.state(), stateManager.currentFlag.ctrl, stateManager.bonusState);

            // Evaluate Result
            if (reelManager.reelsState == ReelsState::Stop){
                stateManager.evaluateResult(reelManager.reelsResult.flag);
                effectManager.checkFlash(reelManager.reelsResult);
                reelManager.reelsState = ReelsState::WaitLever;
                cout << "Coin: " << stateManager.coin << endl;
            }

            // Effect
            effectManager.updateFlash(dt, reelManager.event);

            // Clear input
            inputManager.clear();
        }

        // Render
        renderer.clear();
        renderer.reels(reelManager.leftReel.reelPos, reelManager.centerReel.reelPos, reelManager.rightReel.reelPos);
        renderer.reelsFlash(effectManager.event.flash);
        renderer.update();

        // SE
        audioManager.SE(reelManager.event, stateManager.event);

        // BGM
        audioManager.BGM(stateManager.event);

        // Clear event
        reelManager.event.clear();
        stateManager.event.clear();
        // effectManager.event.clear();
    }
};

void Game::exit(){
    renderer.exit();
    audioManager.exit();
};


