#pragma once
#include <string_view>
using namespace std;

enum class ReelCtrl{
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

ReelCtrl to_ReelCtrl(string_view str);
