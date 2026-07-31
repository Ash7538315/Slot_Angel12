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

namespace SlotFlag{
    constexpr Flag miss{
        .name = "miss",
        .allocateNum = 0,
        .payout = 0,
        .ctrl = CtrlFlag::Miss,
        .result = ResultFlag::Miss
    };

    constexpr Flag replay{
        .name = "replay",
        .allocateNum = 8978,
        .payout = 0,
        .ctrl = CtrlFlag::Replay,
        .result = ResultFlag::Replay
    };

    constexpr Flag bell{
        .name = "bell",
        .allocateNum = 6827,
        .payout = 9,
        .ctrl = CtrlFlag::Bell,
        .result = ResultFlag::Bell
    };

    constexpr Flag suikaA{
        .name = "suikaA",
        .allocateNum = 811,
        .payout = 12,
        .ctrl = CtrlFlag::SuikaA,
        .result = ResultFlag::Suika
    };

    constexpr Flag suikaB{
        .name = "suikaB",
        .allocateNum = 510,
        .payout = 12,
        .ctrl = CtrlFlag::SuikaB,
        .result = ResultFlag::Suika
    };

    constexpr Flag cherry{
        .name = "cherry",
        .allocateNum = 2010,
        .payout = 4,
        .ctrl = CtrlFlag::Cherry,
        .result = ResultFlag::Cherry
    };

    constexpr Flag redBB{
        .name = "redBB",
        .allocateNum = 140,
        .payout = 0,
        .ctrl = CtrlFlag::RedBB,
        .result = ResultFlag::RedBB
    };

    constexpr Flag blueBB{
        .name = "blueBB",
        .allocateNum = 140,
        .payout = 0,
        .ctrl = CtrlFlag::BlueBB,
        .result = ResultFlag::BlueBB
    };

    constexpr Flag RB{
        .name = "RB",
        .allocateNum = 140,
        .payout = 0,
        .ctrl = CtrlFlag::RB,
        .result = ResultFlag::RB
    };

    constexpr Flag bBell{
        .name = "bBell",
        .allocateNum = 65536,
        .payout = 12,
        .ctrl = CtrlFlag::BBell,
        .result = ResultFlag::BBell
    };

    constexpr Flag cBell{
        .name = "cBell",
        .allocateNum = 0, // Overlap with BBell
        .payout = 11,
        .ctrl = CtrlFlag::BBell,
        .result = ResultFlag::CBell
    };

    constexpr Flag none{
        .name = "none",
        .allocateNum = 0,
        .payout = 0,
        .ctrl = CtrlFlag::Miss,
        .result = ResultFlag::BadPattern
};
}



inline const array<Flag, 5> roleFlags{
    SlotFlag::replay,
    SlotFlag::bell,
    SlotFlag::suikaA,
    SlotFlag::suikaB,
    SlotFlag::cherry
};

inline const array<Flag, 3> bonusFlags{
    SlotFlag::redBB,
    SlotFlag::blueBB,
    SlotFlag::RB
};

inline const array<Flag, 2> roleFlagsInBB{
    SlotFlag::bBell,
    SlotFlag::cBell
};
