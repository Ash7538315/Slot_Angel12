#pragma once
#include <filesystem>
#include "Renderer.hpp"
#include "FlagManager.hpp"
#include "SDL3/SDL_events.h"

using namespace std;
namespace fs = filesystem;

struct GameConst{
    static inline const char* windowTitle = "Angel12";
    static inline const fs::path rootPath = PROJECT_ROOT;
    static inline const double timestep = 1.00 / 60.00;  // 60 fps
};

class Game{
private:
    FlagLottery flagDrawer;
    Renderer renderer;

    void update(const SDL_Event& event);
    bool running;
public:
    void init();
    void run();
    void exit();
};
