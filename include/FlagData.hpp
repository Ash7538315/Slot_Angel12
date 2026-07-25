#pragma once
#include <string>
#include <array>
#include "ReelData.hpp"

using namespace std;

namespace SlotStateConst{
    constexpr int MAX_BB_PAYOUT = 300;
    constexpr int MAX_BB_GAMECOUNT = 32;
    constexpr int MAX_RB_PAYOUT = 135;
    constexpr int MAX_RB_GAMECOUNT = 8;
}

struct Flag{
    string name;
    int allocateNum;
    int payout;
    CtrlFlag ctrl;
    ResultFlag result;
    bool operator==(const Flag&) const = default;
};

inline const Flag miss{
    .name = "miss",
    .allocateNum = 0,
    .payout = 0,
    .ctrl = CtrlFlag::Miss,
    .result = ResultFlag::Miss
};

inline const Flag replay{
    .name = "replay",
    .allocateNum = 8978,
    .payout = 0,
    .ctrl = CtrlFlag::Replay,
    .result = ResultFlag::Replay
};

inline const Flag bell{
    .name = "bell",
    .allocateNum = 6827,
    .payout = 9,
    .ctrl = CtrlFlag::Bell,
    .result = ResultFlag::Bell
};

inline const Flag suikaA{
    .name = "suikaA",
    .allocateNum = 811,
    .payout = 12,
    .ctrl = CtrlFlag::SuikaA,
    .result = ResultFlag::Suika
};

inline const Flag suikaB{
    .name = "suikaB",
    .allocateNum = 510,
    .payout = 12,
    .ctrl = CtrlFlag::SuikaB,
    .result = ResultFlag::Suika
};

inline const Flag cherry{
    .name = "cherry",
    .allocateNum = 2010,
    .payout = 4,
    .ctrl = CtrlFlag::Cherry,
    .result = ResultFlag::Cherry
};

inline const Flag redBB{
    .name = "redBB",
    .allocateNum = 140,
    .payout = 0,
    .ctrl = CtrlFlag::RedBB,
    .result = ResultFlag::RedBB
};

inline const Flag blueBB{
    .name = "blueBB",
    .allocateNum = 140,
    .payout = 0,
    .ctrl = CtrlFlag::BlueBB,
    .result = ResultFlag::BlueBB
};

inline const Flag RB{
    .name = "RB",
    .allocateNum = 140,
    .payout = 0,
    .ctrl = CtrlFlag::RB,
    .result = ResultFlag::RB
};

inline const Flag bBell{
    .name = "bBell",
    .allocateNum = 65536,
    .payout = 12,
    .ctrl = CtrlFlag::BBell,
    .result = ResultFlag::BBell
};

inline const Flag cBell{
    .name = "cBell",
    .allocateNum = 0, // Overlap with BBell
    .payout = 11,
    .ctrl = CtrlFlag::BBell,
    .result = ResultFlag::CBell
};

inline const Flag none{
    .name = "none",
    .allocateNum = 0,
    .payout = 0,
    .ctrl = CtrlFlag::Unctrl,
    .result = ResultFlag::BadPattern
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

inline const array<Flag, 2> roleFlagsInBB{
    bBell,
    cBell
};
