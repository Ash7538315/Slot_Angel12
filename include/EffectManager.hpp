#pragma once
#include "ReelManager.hpp"
#include "StateManager.hpp"

struct FlashState{
    bool isFlash = false;
    float leftFlashPos;
    float centerFlashPos;
    float rightFlashPos;
};

struct EffectEvent{
    FlashState flash;
    
    void clear() {
        *this = EffectEvent{};
    }
};

class EffectManager{
private:
    bool isFlash;
    double flashTime;
public:
    EffectEvent event;

    void init();
    void checkFlash(const ReelsResult reelsResult);
    void updateFlash(const double& dt, const ReelEvent& reelEvent);
};
