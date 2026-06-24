#pragma once
#include <string>
#include <array>
#include "ReelData.hpp"

using namespace std;

struct Flag{
    string name;
    int allocateNum;
    int payout;
    CtrlFlag ctrl;
};

inline const Flag miss{
    .name = "miss",
    .allocateNum = 65536,
    .payout = 0,
    .ctrl = CtrlFlag::Miss
};

inline const Flag replay{
    .name = "replay",
    .allocateNum = 8978,
    .payout = 0,
    .ctrl = CtrlFlag::Replay
};

inline const Flag bell{
    .name = "bell",
    .allocateNum = 6827,
    .payout = 9,
    .ctrl = CtrlFlag::Bell
};

inline const Flag suikaA{
    .name = "suikaA",
    .allocateNum = 811,
    .payout = 12,
    .ctrl = CtrlFlag::SuikaA
};

inline const Flag suikaB{
    .name = "suikaB",
    .allocateNum = 510,
    .payout = 12,
    .ctrl = CtrlFlag::SuikaB
};

inline const Flag cherry{
    .name = "cherry",
    .allocateNum = 2010,
    .payout = 4,
    .ctrl = CtrlFlag::Cherry
};

inline const Flag redBB{
    .name = "redBB",
    .allocateNum = 140,
    .payout = 0,
    .ctrl = CtrlFlag::RedBB
};

inline const Flag blueBB{
    .name = "blueBB",
    .allocateNum = 140,
    .payout = 0,
    .ctrl = CtrlFlag::BlueBB
};

inline const Flag RB{
    .name = "RB",
    .allocateNum = 140,
    .payout = 0,
    .ctrl = CtrlFlag::RB
};

inline const array<Flag, 5> roleFlags{
    replay,
    bell,
    suikaA,
    suikaB,
    cherry
};

inline const array<Flag, 3> bonusFlags{
    redBB,
    blueBB,
    RB
};
