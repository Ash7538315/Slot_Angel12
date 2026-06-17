#pragma once
#include "SDL3/SDL.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_main.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"

class Renderer{
private:
    SDL_Window* window;
    SDL_Renderer* renderer; 

    SDL_Texture* leftReel;

public:
    void init();
    void update();
    void exit();

    void initTest();
    void runTest();
};
