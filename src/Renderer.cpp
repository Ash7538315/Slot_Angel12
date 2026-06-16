#include "Game.hpp"
#include "Renderer.hpp"
#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

void Renderer::init(){
    Renderer::window = SDL_CreateWindow(
        GameConst::windowTitle,            // window title
        640,                                   // width, in pixels
        480,                                   // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );
}

