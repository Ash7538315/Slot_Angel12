#pragma once
#include "GameConst.hpp"
#include "SDL3/SDL_render.h"
#include "SDL3_ttf/SDL_ttf.h"

class Renderer{
private:
    SDL_Window* window;
    SDL_Renderer* renderer; 
    
    SDL_FRect src;
    SDL_FRect dst;

    SDL_Texture* leftReel;
    SDL_Texture* centerReel;
    SDL_Texture* rightReel;

    TTF_Font* font;
    TTF_TextEngine* engine;


    void reelDraw(SDL_Texture* reelImg, const float reelPos, const SDL_FRect dst);

public:
    void init();
    void title();
    void reelUpdate(const float& leftReelPos, const float& centerReelPos, const float& rightReelPos);
    void exit();
;
};
