#pragma once
#include <array>
#include <vector>
#include <map>

using namespace std;

enum class CtrlFlag{
    Unctrl,
    Miss,
    Bell,
    Replay,
    SuikaA,
    SuikaB,
    Cherry,
    RedBB,
    BlueBB,
    RB,
};

enum class ResultFlag{
    Miss,
    BonusReachPattern,
    BadPattern,
    Bell,
    Replay,
    Suika,
    Cherry,
    RedBB,
    BlueBB,
    RB
};

enum class Symbol{
    None,
    Bell,
    Replay,
    Suika,
    Cherry,
    RedSeven,
    BlueSeven,
    Bar,
    Blank, 
};

struct LineResult{
    Symbol left;
    Symbol center;
    Symbol right;

    ResultFlag resultFlag;
};

constexpr array<LineResult, 10> winningCombinationTable{{
    {Symbol::Bell, Symbol::Bell, Symbol::Bell, ResultFlag::Bell},
    {Symbol::Replay, Symbol::Replay, Symbol::Replay, ResultFlag::Replay},
    {Symbol::Cherry, Symbol::Bell, Symbol::Cherry, ResultFlag::Cherry},
    {Symbol::Cherry, Symbol::Bell, Symbol::BlueSeven, ResultFlag::Cherry},
    {Symbol::Cherry, Symbol::Bell, Symbol::Blank, ResultFlag::Cherry},
    {Symbol::Suika, Symbol::Suika, Symbol::Suika, ResultFlag::Suika},
    {Symbol::Suika, Symbol::Suika, Symbol::Bar, ResultFlag::Suika},
    {Symbol::RedSeven, Symbol::RedSeven, Symbol::RedSeven, ResultFlag::RedBB},
    {Symbol::BlueSeven, Symbol::BlueSeven, Symbol::BlueSeven, ResultFlag::BlueBB},
    {Symbol::Bar, Symbol::Bar, Symbol::Bar, ResultFlag::RB},
}};

constexpr array<LineResult, 28> bonusReachCombinationTable{{
    {Symbol::Bar, Symbol::Replay, Symbol::Replay, ResultFlag::BonusReachPattern},
    {Symbol::Bar, Symbol::RedSeven, Symbol::RedSeven, ResultFlag::BonusReachPattern},
    {Symbol::Bar, Symbol::RedSeven, Symbol::BlueSeven, ResultFlag::BonusReachPattern},
    {Symbol::Bar, Symbol::RedSeven, Symbol::Bar, ResultFlag::BonusReachPattern},
    {Symbol::Bar, Symbol::BlueSeven, Symbol::BlueSeven, ResultFlag::BonusReachPattern},
    {Symbol::Bar, Symbol::BlueSeven, Symbol::RedSeven, ResultFlag::BonusReachPattern},
    {Symbol::Bar, Symbol::BlueSeven, Symbol::Bar, ResultFlag::BonusReachPattern},
    {Symbol::Bar, Symbol::Bar, Symbol::RedSeven, ResultFlag::BonusReachPattern},
    {Symbol::Bar, Symbol::Bar, Symbol::BlueSeven, ResultFlag::BonusReachPattern},
    {Symbol::RedSeven, Symbol::Cherry, Symbol::Cherry, ResultFlag::BonusReachPattern},
    {Symbol::Suika, Symbol::Suika, Symbol::RedSeven, ResultFlag::BonusReachPattern},
    {Symbol::RedSeven, Symbol::RedSeven, Symbol::BlueSeven, ResultFlag::BonusReachPattern},
    {Symbol::RedSeven, Symbol::RedSeven, Symbol::Bar, ResultFlag::BonusReachPattern},
    {Symbol::RedSeven, Symbol::BlueSeven, Symbol::BlueSeven, ResultFlag::BonusReachPattern},
    {Symbol::RedSeven, Symbol::BlueSeven, Symbol::Bar, ResultFlag::BonusReachPattern},
    {Symbol::RedSeven, Symbol::BlueSeven, Symbol::RedSeven, ResultFlag::BonusReachPattern},
    {Symbol::RedSeven, Symbol::Bar, Symbol::RedSeven, ResultFlag::BonusReachPattern},
    {Symbol::RedSeven, Symbol::Bar, Symbol::BlueSeven, ResultFlag::BonusReachPattern},
    {Symbol::RedSeven, Symbol::Bar, Symbol::Bar, ResultFlag::BonusReachPattern},
    {Symbol::BlueSeven, Symbol::Bar, Symbol::Bar, ResultFlag::BonusReachPattern},
    {Symbol::BlueSeven, Symbol::Bar, Symbol::BlueSeven, ResultFlag::BonusReachPattern},
    {Symbol::BlueSeven, Symbol::Bar, Symbol::RedSeven, ResultFlag::BonusReachPattern},
    {Symbol::BlueSeven, Symbol::RedSeven, Symbol::RedSeven, ResultFlag::BonusReachPattern},
    {Symbol::BlueSeven, Symbol::RedSeven, Symbol::BlueSeven, ResultFlag::BonusReachPattern},
    {Symbol::BlueSeven, Symbol::RedSeven, Symbol::Bar, ResultFlag::BonusReachPattern},
    {Symbol::BlueSeven, Symbol::BlueSeven, Symbol::RedSeven, ResultFlag::BonusReachPattern},
    {Symbol::BlueSeven, Symbol::BlueSeven, Symbol::Bar, ResultFlag::BonusReachPattern},
    {Symbol::BlueSeven, Symbol::Bell, Symbol::Bell, ResultFlag::BonusReachPattern},
}};

constexpr array<Symbol, 21> leftReelStrips{
    Symbol::Bell,
    Symbol::RedSeven,
    Symbol::RedSeven,
    Symbol::Replay,
    Symbol::Bell,
    Symbol::Suika,
    Symbol::Cherry,
    Symbol::Bell,
    Symbol::Bar,
    Symbol::Suika,
    Symbol::Replay,
    Symbol::Suika,
    Symbol::Bell,
    Symbol::RedSeven,
    Symbol::Cherry,
    Symbol::BlueSeven,
    Symbol::Bell,
    Symbol::Replay,
    Symbol::Suika,
    Symbol::Bell,
    Symbol::Blank
};

constexpr array<Symbol, 21> centerReelStrips{
    Symbol::Bell,
    Symbol::Replay,
    Symbol::Suika,
    Symbol::RedSeven,
    Symbol::Cherry,
    Symbol::Bell,
    Symbol::Replay,
    Symbol::Bar,
    Symbol::Cherry,
    Symbol::Bell,
    Symbol::Replay,
    Symbol::Suika,
    Symbol::RedSeven,
    Symbol::Replay,
    Symbol::Bell,
    Symbol::BlueSeven,
    Symbol::Cherry,
    Symbol::Replay,
    Symbol::Bell,
    Symbol::Blank,
    Symbol::Cherry
};

constexpr array<Symbol, 21> rightReelStrips{
    Symbol::Suika,
    Symbol::Replay,
    Symbol::Cherry,
    Symbol::RedSeven,
    Symbol::Bell,
    Symbol::Suika,
    Symbol::Replay,
    Symbol::Cherry,
    Symbol::Bell,
    Symbol::Replay,
    Symbol::Bar,
    Symbol::Cherry,
    Symbol::Bell,
    Symbol::Suika,
    Symbol::Replay,
    Symbol::BlueSeven,
    Symbol::Bell,
    Symbol::Suika,
    Symbol::Replay,
    Symbol::Blank,
    Symbol::Bell
};

using SlipTable = array<int, 21>;
inline const map<CtrlFlag, SlipTable> leftSlipTables {
    {CtrlFlag::Miss, {3,4,0,1,1,3,4,0,0,1,2,0,1,2,3,0,1,2,0,1,2}},
    {CtrlFlag::Bell, {0,1,0,1,1,2,3,0,1,2,3,4,1,2,3,0,1,2,1,2,3}},
    {CtrlFlag::Replay, {4,0,0,0,1,2,3,4,0,1,2,3,2,3,4,0,1,0,1,2,3}},
    {CtrlFlag::Cherry, {2,3,4,0,0,1,0,1,2,3,4,0,0,1,0,1,2,3,0,0,1}},
    {CtrlFlag::SuikaA, {3,4,0,0,1,2,3,0,1,2,3,0,1,2,3,4,0,0,0,1,2}},
    {CtrlFlag::SuikaB, {3,4,0,0,1,2,3,0,1,0,0,0,1,2,3,4,0,0,0,1,2}},
    {CtrlFlag::RedBB, {0,0,1,1,2,3,4,4,1,2,3,0,1,2,3,4,0,0,0,1,2}},
    {CtrlFlag::BlueBB, {3,40,0,1,2,3,0,0,3,4,3,2,3,4,0,1,2,3,4,1}},
    {CtrlFlag::RB, {3,4,0,0,1,2,3,0,1,1,2,3,4,2,3,4,1,2,0,1,2}}
};

inline const  map<CtrlFlag, SlipTable> centerSlipTables{};
inline const map<CtrlFlag, SlipTable> rightSlipTables{};

inline const map<CtrlFlag, vector<Symbol>> leftTargetSymbolTable{
    {CtrlFlag::Miss, {Symbol::None}},
    {CtrlFlag::Bell, {Symbol::Bell}},
    {CtrlFlag::Replay, {Symbol::Replay}},
    {CtrlFlag::Cherry, {Symbol::Cherry}},
    {CtrlFlag::SuikaA, {Symbol::Suika}},
    {CtrlFlag::SuikaB, {Symbol::Suika}},
    {CtrlFlag::RedBB, {Symbol::RedSeven}},
    {CtrlFlag::BlueBB, {Symbol::BlueSeven}},
    {CtrlFlag::RB, {Symbol::Bar}}
};

inline const map<CtrlFlag, vector<Symbol>> centerTargetSymbolTable{
    {CtrlFlag::Bell, {Symbol::Bell}},
    {CtrlFlag::Replay, {Symbol::Replay}},
    {CtrlFlag::Cherry, {Symbol::Cherry}},
    {CtrlFlag::SuikaA, {Symbol::Suika}},
    {CtrlFlag::SuikaB, {Symbol::Suika}},
    {CtrlFlag::RedBB, {Symbol::RedSeven}},
    {CtrlFlag::BlueBB, {Symbol::BlueSeven}},
    {CtrlFlag::RB, {Symbol::Bar}}
};

inline const map<CtrlFlag, vector<Symbol>> rightTargetSymbolTable{
    {CtrlFlag::Miss, {Symbol::RedSeven, Symbol::BlueSeven, Symbol::Replay}},
    {CtrlFlag::Bell, {Symbol::Bell}},
    {CtrlFlag::Replay, {Symbol::Replay}},
    {CtrlFlag::Cherry, {Symbol::Cherry, Symbol::BlueSeven, Symbol::Blank}},
    {CtrlFlag::SuikaA, {Symbol::Suika, Symbol::Bar}},
    {CtrlFlag::SuikaB, {Symbol::Suika, Symbol::Bar}},
    {CtrlFlag::RedBB, {Symbol::RedSeven}},
    {CtrlFlag::BlueBB, {Symbol::BlueSeven, Symbol::Cherry, Symbol::Blank, Symbol::Bell}},
    {CtrlFlag::RB, {Symbol::Bar}}
};
