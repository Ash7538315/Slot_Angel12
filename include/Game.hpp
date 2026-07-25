#pragma once
#include "AudioManager.hpp"
#include "InputManager.hpp"
#include "ReelManager.hpp"
#include "Renderer.hpp"
#include "StateManager.hpp"
#include "EffectManager.hpp"

class Game{
private:
    StateManager stateManager;
    Renderer renderer;
    InputManager inputManager;
    ReelManager reelManager;
    AudioManager audioManager;
    EffectManager effectManager;

    bool running;
public:
    void init();
    void run();
    void exit();
};
