#pragma once
#include "GameConst.hpp"
#include "SDL3/SDL_render.h"

class Renderer{
private:
    SDL_Window* window;
    SDL_Renderer* renderer; 
    
    SDL_FRect src;
    SDL_FRect dst;

    SDL_Texture* leftReel;

    void reelDraw(SDL_Texture* reelImg, const float reelScrollY, const SDL_FRect dst);

public:
    void init();

    void setScrollY();
    void update(const float leftReelScrollY);
    void exit();

    void initTest();
    void runTest();
};
