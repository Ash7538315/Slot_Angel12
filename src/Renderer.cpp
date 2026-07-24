#include "GameConst.hpp"
#include "Renderer.hpp" 
#include "SDL3_image/SDL_image.h"
#include "SDL3_ttf/SDL_ttf.h"

void Renderer::init(){
    window = SDL_CreateWindow(
        GameConst::windowTitle,            // window title
        GameConst::windowWidth,// width, in pixels
        GameConst::windowHeight,                              // height, in pixels
        0                                  // flags - see below  prev: SDL_WINDOW_OPENGL
    );
    renderer = SDL_CreateRenderer(window, nullptr);

    leftReel = IMG_LoadTexture(renderer, (GameConst::rootPath / "asset/img/left_reel.png").string().c_str());
    centerReel = IMG_LoadTexture(renderer, (GameConst::rootPath / "asset/img/center_reel.png").string().c_str());
    rightReel = IMG_LoadTexture(renderer, (GameConst::rootPath / "asset/img/right_reel.png").string().c_str());

    font = TTF_OpenFont("../assets/fonts/PlayfairDisplay-VariableFont_wght.ttf", 36);
    engine = TTF_CreateRendererTextEngine(renderer);
}

void Renderer::reelDraw(SDL_Texture* reelImg, const float ReelPos, const SDL_FRect dst){
    SDL_FRect src{
    0,                                                                  // x
    ReelPos,                                                            // y
    GameConst::symbolWidth,                                             // w
    GameConst::symbollHeight * 3 + GameConst::symbollHeight / 6.0       // h
    };

    SDL_RenderTexture(renderer, reelImg, &src, &dst);
};

void Renderer::title(){
    // SDL_RenderClear(renderer);
    // TTF_Text* text = TTF_CreateText(engine, font, "Hello, SDL3!", 0);
    // if (!text) {
    // SDL_Log("Text creation failed: %s", SDL_GetError());
    // }
    // TTF_SetTextColor(text, 1.0f, 1.0f, 1.0f, 1.0f);
    // TTF_DrawRendererText(text, 100.0f, 100.0f);
    // SDL_RenderPresent(renderer);
}

void Renderer::reelUpdate(const float& leftReelPos, const float& centerReelPos, const float& rightReelPos){
    // Clear
    SDL_RenderClear(renderer);

    // Render reel
    reelDraw(leftReel , leftReelPos, GameConst::leftDst);
    reelDraw(centerReel , centerReelPos, GameConst::centerDst);
    reelDraw(rightReel , rightReelPos, GameConst::rightDst);

    // Update
    SDL_RenderPresent(renderer);
}

void Renderer::exit(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
};

