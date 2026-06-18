#pragma once
#include <filesystem>
#include "SDL3_image/SDL_image.h"

using namespace std;
namespace fs = filesystem;

namespace GameConst{
    inline constexpr const char* windowTitle = "Angel12";
    inline fs::path rootPath = PROJECT_ROOT;

    inline constexpr int symbolWidth = 300;
    inline constexpr int symbollHeight = 132;

    inline constexpr double timestep = 1.00 / 60.01;
    inline constexpr int nsymbol = 21;
    inline constexpr float scrollSpeed = nsymbol * symbollHeight / 0.85 * timestep;

    inline constexpr SDL_FRect leftDst{
        0, // x
        0, // y
        GameConst::symbolWidth,  // w
        GameConst::symbollHeight * 3 + GameConst::symbollHeight / 6.0   // h
    };
};
