#pragma once
#include "GameConst.hpp"
#include <future>
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
    BlueBB
};

ReelCtrlFlag to_ReelCtrlFlag(string_view str);

class Reel{
public:
    float ReelScrollY = GameConst::symbollHeight * 4;
    int symbolIndex();
};

class ReelCtrl{
public:
    Reel leftReel;
    Reel centerReel;
    Reel rightReel;

    void init();
    void leftCtrl();
};
