#pragma once
#include "InputManager.hpp"
#include "ReelCtrl.hpp"
#include "Renderer.hpp"
#include "FlagManager.hpp"

class Game{
private:
    FlagLottery flagDrawer;
    Renderer renderer;
    InputManager inputManager;
    ReelCtrl reelCtrl;

    bool running;
    void update();
public:
    void init();
    void run();
    void exit();
};
