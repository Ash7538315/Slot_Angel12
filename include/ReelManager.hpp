#pragma once
#include "GameConst.hpp"
#include "InputManager.hpp"
#include <string_view>
using namespace std;

enum class ReelCtrlFlag{
    Replay,
    Cherry,
    SuikaA,
    SuikaB,
    Bell,
    Miss,
    RB,
    RedBB,
    BlueBB,
    Unctrl
};

ReelCtrlFlag to_ReelCtrlFlag(string_view str);

class ReelCtrl{
public: 
    void init();
    int calcStopSymbolIndex(int symbolIndex, ReelCtrlFlag reelCtrlFlag);
};

enum class ReelState{
    Spin,
    Stop,
    Wait,
};

class Reel{
private:
    float stopScrollY(const int& symbolIndex);
public:
    ReelState state;
    float reelScrollY;
    int symbolIndex();
    int stopSymbolIndex;
    void updateScrollY();
};

class ReelManager{
private:
    void startSpin();
    ReelState reelsState;

public:
    Reel leftReel;
    Reel centerReel;
    Reel rightReel;

    ReelCtrl leftCtrl;
    ReelCtrl centerCtrl;
    ReelCtrl rightCtrl;
    
    void init();
    void ctrl(const InputStates& inputStates);
};
