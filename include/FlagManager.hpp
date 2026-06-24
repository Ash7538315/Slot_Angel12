#pragma once
#include <random>
#include "FlagData.hpp"

using namespace std;

enum class BonusStates{
    NotBonus,
    HasBonus,
    InBonus,
};

class FlagManager{
private:
    mt19937 rng{random_device{}()};
    uniform_int_distribution<uint16_t> dist{0, 65535};

public:
    Flag currentFlag;
    BonusStates bonusState;
    Flag hasBonusFlag;
    void init();
    void draw();
};
