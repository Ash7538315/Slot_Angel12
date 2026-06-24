#pragma once
#include "SDL3/SDL_timer.h"
#include "InputManager.hpp"
#include "ReelData.hpp"
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

struct ReelResult{
    Symbol top;
    Symbol middle;
    Symbol bottom;
};

class ReelCtrl{
protected:
    const map<CtrlFlag, SlipTable>* slipTable;
    const array<Symbol, 21>* reelStrips;
    const map<CtrlFlag, vector<Symbol>>* targetSymbolTable;
    vector<int> calcCanStopIndex();
    int currentStopSymbolIndex;
public: 
    void init(const array<Symbol, 21>& ReelStrips, const map<CtrlFlag, SlipTable>& SlipTable, const map<CtrlFlag, vector<Symbol>>& TargetSymbolTable);
    int firstStopSymbolIndex(const int& symbolIndex, const CtrlFlag& ctrlFlag);
    ReelRow targetSymbolRow(const CtrlFlag& ctrlFlag);
    virtual int secondStopSymbolIndex(const int& symbolIndex, const CtrlFlag& ctrlFlag, const ReelRow& firstTargetSymbolRow){return 0;};
    ReelResult reelResult();
    virtual int thirdStopSymbolIndex(const int& symbolIndex, const CtrlFlag& ctrlFlag, const ReelResult& firstReelResult, const ReelResult& secondReelResult){return 0;};

    static ResultFlag checkResultFlag(const ReelResult& leftReelResult, const ReelResult& centerReelResult, const ReelResult& rightReelResult);
};

class LeftReelCtrl : public ReelCtrl{};

class CenterReelCtrl : public ReelCtrl{
public:
    int thirdStopSymbolIndex(const int& symbolIndex, const CtrlFlag& ctrlFlag, const ReelResult& leftReelResult, const ReelResult& rightReelResult);
};

class RightReelCtrl : public ReelCtrl{
public:
    int secondStopSymbolIndex(const int& symbolIndex, const CtrlFlag& ctrlFlag, const ReelRow& leftTargetSymbolRow);
};

enum class ReelState{
    Spin,
    Stop,
    Wait,
};

class Reel{
private:
    float stopScrollY(const int& symbolIndex);
public:
    ReelState state;
    float reelScrollY;
    int symbolIndex();
    int stopSymbolIndex;
    void updateScrollY();
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

    Reel leftReel;
    Reel centerReel;
    Reel rightReel;
    ReelState reelsState;

    LeftReelCtrl leftCtrl;
    CenterReelCtrl centerCtrl;
    RightReelCtrl rightCtrl;

    
    void init();
    void ctrl(const InputStates& inputStates, const CtrlFlag& ctrlFlag);
};
