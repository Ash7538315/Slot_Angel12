#include "Game.hpp"
#include "Renderer.hpp"
#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

void Renderer::init(){
    window = SDL_CreateWindow(
        GameConst::windowTitle,            // window title
        640,                                   // width, in pixels
        480,                                   // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );
    renderer = SDL_CreateRenderer(window, nullptr);
}

void Renderer::runTest(){   
};

void Renderer::exit(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
};

