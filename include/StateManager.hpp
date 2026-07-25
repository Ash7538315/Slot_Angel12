#pragma once
#include <random>
#include <span>
#include "FlagData.hpp"

using namespace std;

enum class BonusState{
    Normal,
    Bonus
};

struct StateEvent{
    bool bet = false;
    bool startRedBB = false;
    bool endBonus = false;

    void clear(){
        *this = {};
    }
};

class StateManager{
private:
    mt19937 rng{random_device{}()};
    uniform_int_distribution<uint16_t> dist{0, 65535};
    Flag selectFlag(const span<const Flag> flags);

    int remainPayput;
    int remainGameCount;
public:
    int totalGameCount; 
    int gameCount;
    int coin;
    bool isBet;
    Flag currentFlag;
    BonusState bonusState;
    Flag hasBonusFlag;
    StateEvent event;
    void init();
    /*
    Bet coin,
    Set isBet to true
    */
    void bet();

    /*draw Flag,
    Set currentFlag
    */
    void drawFlag();

    /*Evaluate Result Flag,
    Update coin gameCount,
    Update bonusState if win bonus,
    Set isBet to false
    */
    void evaluateResult(const ResultFlag& reelResult);
};
