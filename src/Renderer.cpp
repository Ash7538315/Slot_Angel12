#include "Game.hpp"
#include "Renderer.hpp" 
#include "SDL3_image/SDL_image.h"

void Renderer::init(){
    window = SDL_CreateWindow(
        GameConst::windowTitle,            // window title
        640,                                   // width, in pixels
        480,                                   // height, in pixels
        0                                  // flags - see below  prev: SDL_WINDOW_OPENGL
    );
    renderer = SDL_CreateRenderer(window, nullptr);

    leftReel = IMG_LoadTexture(renderer, "../assets/img/left_reel.png");
}

void Renderer::update(){}

void Renderer::exit(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
};

void Renderer::initTest(){
    
}
