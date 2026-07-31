#pragma once
#include "SDL3/SDL_timer.h"
#include "InputManager.hpp"
#include "StateManager.hpp"
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
    WaitStop,
};

enum ReelsState{
    Spin,
    Stop,
    WaitStart,
    WaitLever
};

enum class WinningLine{
    Top,
    Middle,
    Bottom,
    Top2Bottom,
    Bottom2Top,
    None,
};

struct ReelsResult{
    ResultFlag flag;
    WinningLine line;
};

ReelsResult check5Line(const ColSymbols& leftStopSymbols, const ColSymbols& centerStopSymbols, const ColSymbols& rightStopSymbols, span<const LineResult> table);
ReelsResult check1Line(const ColSymbols& leftStopSymbols, const ColSymbols& centerStopSymbols, const ColSymbols& rightStopSymbols, span<const LineResult> table);

// class Reel{
// protected:
//     const map<CtrlFlag, SlipTable>* slipTable;
//     const array<Symbol, 21>* reelStrips;
//     const map<CtrlFlag, vector<Symbol>>* targetSymbolTable;
//     float stopReelPos(const int& symbolIndex);
//     /* ex.
//     top = Bell,
//     middle = Replay,
//     bottom = RedSeven
//     */
//     ColSymbols colSymbols(const int& posIndex);
// public:
//     void init(const array<Symbol, 21>& ReelStrips, const map<CtrlFlag, SlipTable>& SlipTable, const map<CtrlFlag, vector<Symbol>>& TargetSymbolTable);
//     ReelState state;
//     // current reel top Position
//     float reelPos;
//     // current reel top Index
//     int posIndex();
//     // stop or going to stop reel top Index
//     int stopPosIndex;
//     // stop col symbols
//     ColSymbols stopSymbols;
//     // stop now?
//     bool stopNow;

//     // search target symbol row
//     ReelRow targetRow(const CtrlFlag& ctrlFlag);
//     void firstStop(const CtrlFlag& ctrlFlag);
//     virtual void secondStop(const CtrlFlag& ctrlFlag, const ReelRow& firstTargetSymbolRow){};
//     virtual void thirdStop(const CtrlFlag& ctrlFlag, const ColSymbols& firstStopSymbols, const ColSymbols& secondStopSymbols, const BonusState& bonusState){};

//     // update reel top Position
//     void updateReelPos();
// };


class Reel{
protected:
    const array<Symbol, ReelConst::nsymbol>* reelStrips;
    const array<SlipTable, ReelConst::nCtrlFlag>* firstSlipTable;
    const array<vector<Symbol>, ReelConst::nCtrlFlag>* targetSymbolTable;

    int calcPosIndex();
    ColSymbols calcColSymbols(const int& posIndex);
public:
    float reelPos;
    float stopReelPos;
    ColSymbols stopColSymbols;
    ReelState state;
    
    void init(
        const array<Symbol, ReelConst::nsymbol>& strips, 
        const array<SlipTable, ReelConst::nCtrlFlag>& slipTable, 
        const array<vector<Symbol>, ReelConst::nCtrlFlag>& targeteSymTable
    );
    void firstStop(const CtrlFlag& ctrlFlag);
    void secondStop();
    void thirdStop();

    void update();
};

class LeftReel : public Reel{};
class CenterReel : public Reel{
public:
    // Not yet available
    // void secondStop(const CtrlFlag& ctrlFlag, const ReelRow& leftTargetSymbolRow);

    void thirdStop(const CtrlFlag& ctrlFlag, const ColSymbols& leftStopSymbols, const ColSymbols& rightStopSymbols, const BonusState& bonusState);
};


class RightReel : public Reel{
public:
    void secondStop(const CtrlFlag& ctrlFlag, const ReelRow& leftTargetSymbolRow);
    
    // Not yet available
    // void thirdStop(const CtrlFlag& ctrlFlag, const ColSymbols& leftStopSymbols, const ColSymbols& centerStopSymbols, const BonusState& bonusState);
};
