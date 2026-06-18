#include "GameConst.hpp"
#include "Renderer.hpp" 
#include "SDL3_image/SDL_image.h"

void Renderer::init(){
    window = SDL_CreateWindow(
        GameConst::windowTitle,            // window title
        900,                                   // width, in pixels
        418,                                   // height, in pixels
        0                                  // flags - see below  prev: SDL_WINDOW_OPENGL
    );
    renderer = SDL_CreateRenderer(window, nullptr);
    leftReel = IMG_LoadTexture(renderer, "../asset/img/left_reel.png");
}

void Renderer::reelDraw(SDL_Texture* reelImg, const float reelScrollY, const SDL_FRect dst){
    SDL_FRect src{
    0,                                                                  // x
    reelScrollY,                                                        // y
    GameConst::symbolWidth,                                             // w
    GameConst::symbollHeight * 3 + GameConst::symbollHeight / 6.0       // h
    };

    SDL_RenderTexture(renderer, reelImg, &src, &dst);
};

void Renderer::update(const float leftReelScrollY){
    SDL_RenderClear(renderer);

    // Render Left reel
    reelDraw(leftReel , leftReelScrollY, GameConst::leftDst);

    SDL_RenderPresent(renderer);
}

void Renderer::exit(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
};

void Renderer::initTest(){
    
}
