#pragma once
#include <array>

using namespace std;

enum class Symbol{
    Bell,
    Replay,
    Suika,
    Cherry,
    RedSeven,
    BlueSeven,
    Bar,
    Blank, 
};


constexpr std::array<Symbol, 21> leftReelStrips{
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

constexpr std::array<Symbol, 21> centeReelStrips{
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

using SlipTable = std::array<int, 21>;
struct FirstSlipTables {
    SlipTable miss;
    SlipTable bell;
    SlipTable replay;
    SlipTable cherry;
    SlipTable suika;
    SlipTable redBB;
    SlipTable blueBB;
    SlipTable RB;
};

constexpr FirstSlipTables leftSlips{
    .miss ={3,4,0,1,1,3,4,0,0,1,2,0,1,2,3,0,1,2,1,2}
};
