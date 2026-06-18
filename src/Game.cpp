#include <iostream>
#include "FlagManager.hpp"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_timer.h"
#include "InputManager.hpp"
#include "Game.hpp"

using namespace std;

void Game::init(){
    flagDrawer.init();
    renderer.init();

};

void Game::run(){
    running = true;

    Uint64 prev = SDL_GetPerformanceCounter();
    Uint64 now = SDL_GetPerformanceCounter();
    double freq = SDL_GetPerformanceFrequency();
    double accum = 0.00;
    double dt;

    while (running) {
        // Time control
        now = SDL_GetPerformanceCounter();
        dt = (now - prev) / freq;
        accum += dt;
        prev = now;

        // Detect Event
        inputManager.check();

        // Update;
        while (accum >= GameConst::timestep){
            accum -= GameConst::timestep;
            update();
            inputManager.clear();
        }
        renderer.update(reelCtrl.leftReel.ReelScrollY);
    }
};

void Game::exit(){
    renderer.exit();
};

void Game::update(){
    if(inputManager.state().quit == true){
        running = false;
    }

    reelCtrl.leftCtrl();
};

