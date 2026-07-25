#include "GameConst.hpp"
#include "Renderer.hpp" 
#include "SDL3_image/SDL_image.h"
#include "SDL3_ttf/SDL_ttf.h"

void Renderer::init(){
    window = SDL_CreateWindow(
        GameConst::windowTitle,            // window title
        GameConst::windowWidth,                // width, in pixels
        GameConst::windowHeight,               // height, in pixels
        0                                  // flags - see below
    );
    renderer = SDL_CreateRenderer(window, nullptr);

    leftReel = IMG_LoadTexture(renderer, "../asset/img/left_reel.png");
    centerReel = IMG_LoadTexture(renderer, "../asset/img/center_reel.png");
    rightReel = IMG_LoadTexture(renderer,"../asset/img/right_reel.png");

    // font = TTF_OpenFont("../assets/fonts/PlayfairDisplay-VariableFont_wght.ttf", 36);
    // engine = TTF_CreateRendererTextEngine(renderer);
}

void Renderer::drawReel(SDL_Texture* reelImg, const float ReelPos, const SDL_FRect dst){
    SDL_FRect src{
    0,                                                                  // x
    ReelPos,                                                            // y
    GameConst::symbolWidth,                                             // w
    GameConst::symbollHeight * 3 + GameConst::symbollHeight / 6.0       // h
    };

    SDL_RenderTexture(renderer, reelImg, &src, &dst);
};

void Renderer::drawFlashRect(const float& flashPosx, const float& flashPosy){
    SDL_FRect flashRect{
    flashPosx,
    flashPosy,
    GameConst::symbolWidth,
    GameConst::symbollHeight
    };

    SDL_RenderFillRect(renderer, &flashRect);
};

// yet
void Renderer::title(){}

void Renderer::clear(){

    SDL_RenderClear(renderer);
};

void Renderer::update(){
    SDL_RenderPresent(renderer);
}

void Renderer::reels(const float& leftReelPos, const float& centerReelPos, const float& rightReelPos){
    drawReel(leftReel , leftReelPos, GameConst::leftDst);
    drawReel(centerReel , centerReelPos, GameConst::centerDst);
    drawReel(rightReel , rightReelPos, GameConst::rightDst);
}

void Renderer::reelsFlash(const FlashState& flashState){
    if (!flashState.isFlash) {
        return;
    }
    
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);

    drawFlashRect(GameConst::reelSpace, flashState.leftFlashPos);
    drawFlashRect(GameConst::reelSpace * 2 + GameConst::symbolWidth, flashState.centerFlashPos);
    drawFlashRect(GameConst::reelSpace * 3 + GameConst::symbolWidth * 2, flashState.rightFlashPos);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
};

void Renderer::exit(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
};

