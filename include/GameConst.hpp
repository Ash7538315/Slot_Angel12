#pragma once
#include <filesystem>
#include "SDL3_image/SDL_image.h"

using namespace std;
namespace fs = filesystem;

namespace GameConst{
    constexpr const char* windowTitle = "Angel12";
    inline fs::path rootPath = PROJECT_ROOT;

    constexpr int symbolWidth = 300;
    constexpr int symbollHeight = 132;

    constexpr double timestep = 1.00 / 60.01;
    constexpr int nsymbol = 21;
    constexpr float scrollSpeed = nsymbol * symbollHeight / 0.85 * timestep;

    constexpr int windowWidth = 960;
    constexpr int windowHeight = 418;

    constexpr double reelWait = 4.1;
    constexpr double startWait = 0.7;  

    constexpr SDL_FRect leftDst{
        15, // x
        0, // y
        GameConst::symbolWidth,  // w
        GameConst::symbollHeight * 3 + GameConst::symbollHeight / 6.0   // h
    };

    constexpr SDL_FRect centerDst{
        330, // x
        0, // y
        GameConst::symbolWidth,  // w
        GameConst::symbollHeight * 3 + GameConst::symbollHeight / 6.0   // h
    };

    constexpr SDL_FRect rightDst{
        645, // x
        0, // y
        GameConst::symbolWidth,  // w
        GameConst::symbollHeight * 3 + GameConst::symbollHeight / 6.0   // h
    };
};
