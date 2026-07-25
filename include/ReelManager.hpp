#pragma once
#include "SDL3/SDL_timer.h"
#include "InputManager.hpp"
#include "StateManager.hpp"
#include "ReelData.hpp"
#include "Reel.hpp"

using namespace std;

struct ReelEvent{
    bool startReel = false;
    bool stopLeftReel = false;
    bool stopCenterReel = false;
    bool stopRightReel = false;

    void clear(){
        *this = {};
    }
};

class ReelManager{
private:
    Uint64 prevStartSpinTime = 0;
    Uint64 now;
    double freq = SDL_GetPerformanceFrequency();
    void startSpin();

public:
    ReelEvent event;

    LeftReel leftReel;
    CenterReel centerReel;
    RightReel rightReel;
    ReelsState reelsState;
    ReelsResult reelsResult;
    
    void init();
    void update(const InputStates& inputStates, const CtrlFlag& ctrlFlag, const BonusState& bonusState);
};

