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
        renderer.update();
    }
};

void Game::exit(){
    renderer.exit();
};

void Game::update(){
    if(inputManager.state().quit == true){
        running = false;
    }
};

void Game::runTest(){
        if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow(
        "Angel12",
        1280,
        720,
        0
    );

    if (!window) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
    }

    SDL_Delay(5000);
}
