#pragma once
#include "InputManager.hpp"
#include "ReelManager.hpp"
#include "Renderer.hpp"
#include "FlagManager.hpp"

class Game{
private:
    FlagLottery flagDrawer;
    Renderer renderer;
    InputManager inputManager;
    ReelManager reelManager;

    bool running;
    void update();
public:
    void init();
    void run();
    void exit();
};
