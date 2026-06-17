#pragma once
#include "SDL3/SDL.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_main.h"
#include "SDL3/SDL_render.h"

class Renderer{
private:
    SDL_Window* window;
    SDL_Renderer* renderer; 

public:
    void init();
    void run();
    void runTest();
    void exit();
};
