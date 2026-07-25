#pragma once
#include "SDL3/SDL_render.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "EffectManager.hpp"

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


    void drawReel(SDL_Texture* reelImg, const float reelPos, const SDL_FRect dst);
    void drawFlashRect(const float& flashPosx, const float& flashPosy);

public:
    void init();
    void title();
    void clear();
    void update();
    void reels(const float& leftReelPos, const float& centerReelPos, const float& rightReelPos);
    void reelsFlash(const FlashState& flashState);
    void exit();
;
};
