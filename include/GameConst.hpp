#pragma once
#include <filesystem>
#include "SDL3_image/SDL_image.h"

using namespace std;
namespace fs = filesystem;

namespace GameConst{
    constexpr const char* windowTitle = "Angel12";
    inline fs::path rootPath = PROJECT_ROOT;

    constexpr int symbolWidth = 300;
    constexpr int symbolHeight = 132;
    constexpr int SymbolMargin = symbolHeight / 12;

    constexpr double timestep = 1.00 / 119.6;
    constexpr int nsymbol = 21;
    constexpr float scrollSpeed = nsymbol * symbolHeight / 0.85 * timestep;

    constexpr int reelSpace = 15;
    constexpr int windowWidth = 960;
    constexpr int windowHeight = 418;

    constexpr double reelWait = 4.1;
    constexpr double startWait = 0.7;  

    constexpr SDL_FRect leftDst{
        reelSpace, // x
        0, // y
        GameConst::symbolWidth,  // w
        GameConst::symbolHeight * 3 + GameConst::symbolHeight / 6.0   // h
    };

    constexpr SDL_FRect centerDst{
        reelSpace * 2 + symbolWidth, // x
        0, // y
        GameConst::symbolWidth,  // w
        GameConst::symbolHeight * 3 + GameConst::symbolHeight / 6.0   // h
    };

    constexpr SDL_FRect rightDst{
        reelSpace * 3 + symbolWidth * 2, // x
        0, // y
        GameConst::symbolWidth,  // w
        GameConst::symbolHeight * 3 + GameConst::symbolHeight / 6.0   // h
    };
};
