#pragma once
#include "SDL3/SDL_timer.h"
#include "InputManager.hpp"
#include "FlagManager.hpp"
#include "ReelData.hpp"
#include <span>
#include <vector>
using namespace std;

enum class ReelRow {
    Top,    // 0
    Middle, // 1
    Bottom, // 2
    None,   // 
};

enum class LineType {
    Horizontal,
    Diagonal
};

struct SlipOptions{
    int slipNum;
    LineType type;
};

constexpr std::array<ReelRow, 3> reelRows{
    ReelRow::Top,
    ReelRow::Middle,
    ReelRow::Bottom
};

struct ColSymbols{
    Symbol top;
    Symbol middle;
    Symbol bottom;
};

enum class ReelState{
    Spin,
    Stop,
    Wait,
    WaitLever,
};


class Reel{
protected:
    const map<CtrlFlag, SlipTable>* slipTable;
    const array<Symbol, 21>* reelStrips;
    const map<CtrlFlag, vector<Symbol>>* targetSymbolTable;
    float stopReelPos(const int& symbolIndex);
    /* ex.
    top = Bell,
    middle = Replay,
    bottom = RedSeven
    */
    ColSymbols colSymbols(const int& posIndex);
public:
    void init(const array<Symbol, 21>& ReelStrips, const map<CtrlFlag, SlipTable>& SlipTable, const map<CtrlFlag, vector<Symbol>>& TargetSymbolTable);
    ReelState state;
    // current reel top Position
    float reelPos;
    // current reel top Index
    int posIndex();
    // stop or going to stop reel top Index
    int stopPosIndex;
    // stop col symbols
    ColSymbols stopSymbols;

    // search target symbol row
    ReelRow targetRow(const CtrlFlag& ctrlFlag);
    void firstStop(const CtrlFlag& ctrlFlag);
    virtual void secondStop(const CtrlFlag& ctrlFlag, const ReelRow& firstTargetSymbolRow){};
    virtual void thirdStop(const CtrlFlag& ctrlFlag, const ColSymbols& firstStopSymbols, const ColSymbols& secondStopSymbols){};

    // update reel top Position
    void updateReelPos();
};

class LeftReel : public Reel{};


class CenterReel : public Reel{
public:
    // Not yet available
    // void secondStop(const CtrlFlag& ctrlFlag, const ReelRow& leftTargetSymbolRow);

    void thirdStop(const CtrlFlag& ctrlFlag, const ColSymbols& leftStopSymbols, const ColSymbols& rightStopSymbols);
};


class RightReel : public Reel{
public:
    void secondStop(const CtrlFlag& ctrlFlag, const ReelRow& leftTargetSymbolRow);
    
    // Not yet available
    // void thirdStop(const CtrlFlag& ctrlFlag, const ColSymbols& leftStopSymbols, const ColSymbols& centerStopSymbols);
};

struct ReelEvent{
    bool startReel;
    bool stopLeftReel;
    bool stopCenterReel;
    bool stopRightReel;

    void clear(){
        *this = {};
    }
};

class ReelManager{
private:
    Uint64 prevStartSpinTime = 0;
    Uint64 now;
    double freq = SDL_GetPerformanceFrequency();
    void startSpin();

public:
    ReelEvent event;

    LeftReel leftReel;
    CenterReel centerReel;
    RightReel rightReel;
    ReelState reelsState;
    ResultFlag reelResult;
    
    void init();
    void ctrl(const InputStates& inputStates, const CtrlFlag& ctrlFlag, const BonusStates& bonusState);
};

ResultFlag check5Line(const ColSymbols& leftStopSymbols, const ColSymbols& centerStopSymbols, const ColSymbols& rightStopSymbols, span<const LineResult> table);
ResultFlag check1Line(const ColSymbols& leftStopSymbols, const ColSymbols& centerStopSymbols, const ColSymbols& rightStopSymbols, span<const LineResult> table);
