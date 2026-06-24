#pragma once
#include "AudioManager.hpp"
#include "InputManager.hpp"
#include "ReelManager.hpp"
#include "Renderer.hpp"
#include "FlagManager.hpp"

class Game{
private:
    FlagManager flagManager;
    Renderer renderer;
    InputManager inputManager;
    ReelManager reelManager;
    AudioManager audioManager;

    bool running;
    void update();
public:
    void init();
    void run();
    void exit();
};
