#include "ReelManager.hpp"
#include "GameConst.hpp"
#include "InputManager.hpp"
#include "ReelData.hpp"
#include <array>
#include <cmath>
#include <strings.h>
#include <vector>
#include <iostream>

using namespace std;

float Reel::stopScrollY(const int& symbolIndex){
    float scrollY = (symbolIndex + 2) * GameConst::symbollHeight - GameConst::symbollHeight / 12.0;
    if (scrollY > GameConst::symbollHeight * GameConst::nsymbol - GameConst::symbollHeight / 12.0){
        scrollY -= GameConst::symbollHeight * GameConst::nsymbol;
    }; 
    return scrollY;
};

int Reel::symbolIndex(){
    int symbolIndex = floor((reelScrollY + GameConst::symbollHeight / 12.0) / GameConst::symbollHeight) - 2;
    if (symbolIndex <= 0) {
        symbolIndex += GameConst::nsymbol;
    }
    return symbolIndex;
};

void Reel::updateScrollY(){
    switch (state) {
        case ReelState::Stop:
            break;
        case ReelState::Spin:
            reelScrollY -= GameConst::scrollSpeed;
            if (reelScrollY <= GameConst::symbollHeight - GameConst::symbollHeight / 12.0) {
                reelScrollY += GameConst::symbollHeight * GameConst::nsymbol;
            }
            break;
        case ReelState::Wait:
            float dscrollY = reelScrollY - stopScrollY(stopSymbolIndex);
            if (dscrollY < 0){
                dscrollY += GameConst::symbollHeight * GameConst::nsymbol;
            }

            if (dscrollY <= GameConst::scrollSpeed) {
                reelScrollY = stopScrollY(stopSymbolIndex);
                state = ReelState::Stop;
            } else {
                reelScrollY -= GameConst::scrollSpeed;
                if (reelScrollY <= GameConst::symbollHeight - GameConst::symbollHeight / 12.0) {
                    reelScrollY += GameConst::symbollHeight * GameConst::nsymbol;
                }
            }
            break;
    }
}

void ReelCtrl::init(const array<Symbol, 21>& ReelStrips, const map<CtrlFlag, SlipTable>& SlipTable, const map<CtrlFlag, vector<Symbol>>& TargetSymbolTable){
    reelStrips = &ReelStrips;
    slipTable = &SlipTable;
    targetSymbolTable = &TargetSymbolTable;
};

int ReelCtrl::firstStopSymbolIndex(const int& symbolIndex, const CtrlFlag& ctrlFlag){
    currentStopSymbolIndex = symbolIndex - slipTable->at(ctrlFlag)[symbolIndex-1];

    if (currentStopSymbolIndex <= 0) {
        currentStopSymbolIndex += GameConst::nsymbol;
}
    return currentStopSymbolIndex;
};

ReelRow ReelCtrl::targetSymbolRow(const CtrlFlag& ctrlFlag){
    for (const ReelRow& row : reelRows) {
        for (const Symbol& targetSymbol : targetSymbolTable->at(ctrlFlag)) {
            if((*reelStrips)[currentStopSymbolIndex+static_cast<int>(row)-1] == targetSymbol){
                return row;
            };
        }
    };

    if (ctrlFlag == CtrlFlag::RedBB || ctrlFlag == CtrlFlag::RB) {
        return ReelRow::Bottom;;
    }

    return ReelRow::None;;
};

ReelResult ReelCtrl::reelResult(){
    int i = currentStopSymbolIndex;
    int j= currentStopSymbolIndex + 1;
    int k= currentStopSymbolIndex + 2;

    if (j > GameConst::nsymbol){
        j -= GameConst::nsymbol;
    };

    if (k > GameConst::nsymbol){
        k -= GameConst::nsymbol;
    };

    ReelResult result = {
        .top = (*reelStrips)[i-1],
        .middle = (*reelStrips)[j-1],
        .bottom = (*reelStrips)[k-1],
    };
    return result;
};

int CenterReelCtrl::thirdStopSymbolIndex(const int& symbolIndex, const CtrlFlag& ctrlFlag, const ReelResult& leftReelResult, const ReelResult& rightReelResult){
    vector<int> slipOptions;
    for (const ResultFlag& resultFlag : ctrlFlag2ResultFlagTable.at(ctrlFlag)) {
        for (int islip = 0; islip <=4; ++islip){
            int loc = symbolIndex - islip;
            if (loc <= 0){
                loc += GameConst::nsymbol;
            };
            currentStopSymbolIndex = loc;
            ReelResult centerReelResult = reelResult();
            ResultFlag checkResultFlag = ReelCtrl::checkResultFlag(leftReelResult, centerReelResult, rightReelResult);
            if (checkResultFlag == resultFlag){
                slipOptions.push_back(islip);
            }
        };
    }

    if (slipOptions.empty()) {
        cerr << "Not Found second Stop Pattern" << endl;
        currentStopSymbolIndex = symbolIndex;
        return currentStopSymbolIndex;
    }

    currentStopSymbolIndex = symbolIndex - slipOptions[0];
    if (currentStopSymbolIndex <= 0){
        currentStopSymbolIndex += GameConst::nsymbol;
    };
    return currentStopSymbolIndex;
};

int RightReelCtrl::secondStopSymbolIndex(const int& symbolIndex, const CtrlFlag& ctrlFlag, const ReelRow& leftTargetSymbolRow){
    vector<ReelRow> stopRowOptions;
    switch (leftTargetSymbolRow) {
        case ReelRow::Top:
            stopRowOptions = {ReelRow::Top, ReelRow::Bottom};
            break;
        case ReelRow::Middle:
            stopRowOptions = {ReelRow::Middle};
            break;
        case ReelRow::Bottom:
            stopRowOptions = {ReelRow::Top, ReelRow::Bottom};
            break;
        case ReelRow::None:
            stopRowOptions = {ReelRow::Middle};
            break;
    }

    vector<SlipOptions> slipOptions; 
    for (const Symbol& symbol : targetSymbolTable->at(ctrlFlag)){
        for (int islip = 0; islip <=4; ++islip){
            for (const ReelRow& row : stopRowOptions){
                int loc = symbolIndex - islip + static_cast<int>(row);
                if (loc<= 0){
                    loc += GameConst::nsymbol;
                } else if (loc > GameConst::nsymbol) {
                    loc -= GameConst::nsymbol;
                };

                if ((*reelStrips)[loc-1] == symbol) {
                    if (row == leftTargetSymbolRow) {
                        slipOptions.push_back({islip, LineType::Horizontal});
                    } else {
                        slipOptions.push_back({islip, LineType::Diagonal});
                    };
                }
            }
        }
    }

    if (slipOptions.empty()) {
        cerr << "Not Found second Stop Pattern" << endl;
        currentStopSymbolIndex = symbolIndex; 
    }

    // Ctrl linetype
    currentStopSymbolIndex = symbolIndex - slipOptions[0].slipNum;
    if (ctrlFlag == CtrlFlag::SuikaB || ctrlFlag == CtrlFlag::RedBB || ctrlFlag == CtrlFlag::RB) {
        for (const SlipOptions& option : slipOptions) {
            if (option.type == LineType::Diagonal) {
                currentStopSymbolIndex = symbolIndex - option.slipNum;
                break;
            }
        }
    }

    if (ctrlFlag == CtrlFlag::SuikaA) {
        for (const SlipOptions& option : slipOptions) {
            if (option.type == LineType::Horizontal) {
                currentStopSymbolIndex = symbolIndex - option.slipNum;
                break;
            }
        }
    }

    if (currentStopSymbolIndex <= 0) {
        currentStopSymbolIndex += GameConst::nsymbol;
    }
    return currentStopSymbolIndex;
};

ResultFlag ReelCtrl::checkResultFlag(const ReelResult& leftReelResult, const ReelResult& centerReelResult, const ReelResult& rightReelResult){
    vector<ResultFlag> resultFlags;
    for (const LineResult& combination : winningCombinationTable) {
        if (leftReelResult.top == combination.left && centerReelResult.top == combination.center && rightReelResult.top == combination.right) {
            resultFlags.push_back(combination.resultFlag);
        };
        if (leftReelResult.middle == combination.left && centerReelResult.middle == combination.center && rightReelResult.middle == combination.right) {
            resultFlags.push_back(combination.resultFlag);
        };
        if (leftReelResult.bottom == combination.left && centerReelResult.bottom == combination.center && rightReelResult.bottom == combination.right) {
            resultFlags.push_back(combination.resultFlag);
        };
        if (leftReelResult.top == combination.left && centerReelResult.middle == combination.center && rightReelResult.bottom == combination.right) {
            resultFlags.push_back(combination.resultFlag);
        };
        if (leftReelResult.bottom == combination.left && centerReelResult.middle == combination.center && rightReelResult.top == combination.right) {
            resultFlags.push_back(combination.resultFlag);
        };
    }

    bool isBonusReachCombination = false;
    for (const LineResult& combination : bonusReachCombinationTable) {
        if (leftReelResult.top == combination.left && centerReelResult.top == combination.center && rightReelResult.top == combination.right) {
            isBonusReachCombination = true;
        };
        if (leftReelResult.middle == combination.left && centerReelResult.middle == combination.center && rightReelResult.middle == combination.right) {
            isBonusReachCombination = true;
        };
        if (leftReelResult.bottom == combination.left && centerReelResult.bottom == combination.center && rightReelResult.bottom == combination.right) {
            isBonusReachCombination = true;
        };
        if (leftReelResult.top == combination.left && centerReelResult.middle == combination.center && rightReelResult.bottom == combination.right) {
            isBonusReachCombination = true;
        };
        if (leftReelResult.bottom == combination.left && centerReelResult.middle == combination.center && rightReelResult.top == combination.right) {
            isBonusReachCombination = true;
        };
    };

    switch (resultFlags.size()) {
        case 0:
            if (isBonusReachCombination) {
                return ResultFlag::BonusReachPattern;
            } else {
                return ResultFlag::Miss;
            };
        case 1:
            if (resultFlags[0] == ResultFlag::Cherry && isBonusReachCombination) {
                return ResultFlag::BadPattern;
            } else {
                return resultFlags[0];
            }
        default:
            return ResultFlag::BadPattern;
    }
};

void ReelManager::init(){
    leftReel.state = ReelState::Stop;
    leftReel.reelScrollY = GameConst::symbollHeight * 3 - GameConst::symbollHeight / 12.0;

    centerReel.state = ReelState::Stop;
    centerReel.reelScrollY = GameConst::symbollHeight * 3 - GameConst::symbollHeight / 12.0;

    rightReel.state = ReelState::Stop;
    rightReel.reelScrollY = GameConst::symbollHeight * 3 - GameConst::symbollHeight / 12.0;

    reelsState = ReelState::Stop;

    leftCtrl.init(leftReelStrips, leftSlipTables, leftTargetSymbolTable);
    centerCtrl.init(centerReelStrips, centerSlipTables, centerTargetSymbolTable);
    rightCtrl.init(rightReelStrips, rightSlipTables, rightTargetSymbolTable);
};

void ReelManager::ctrl(const InputStates& inputStates, const CtrlFlag& ctrlFlag){
    event.clear();
    now = SDL_GetPerformanceCounter();
    double dt = (now - prevStartSpinTime) / freq;

    // Lever on
    if (reelsState == ReelState::Stop && inputStates.lever == true) {
        reelsState = ReelState::Wait;
    }

    // left reel
    if ( dt >= GameConst::startWait && inputStates.left == true && leftReel.state == ReelState::Spin ){
        leftReel.state = ReelState::Wait;
        leftReel.stopSymbolIndex = leftCtrl.firstStopSymbolIndex(leftReel.symbolIndex(), ctrlFlag);
        event.stopLeftReel = true;
    };

    // center reel
    if (inputStates.center == true && centerReel.state == ReelState::Spin && leftReel.state != ReelState::Spin && rightReel.state != ReelState::Spin ){
        centerReel.state = ReelState::Wait;
        centerReel.stopSymbolIndex = centerCtrl.thirdStopSymbolIndex(centerReel.symbolIndex(), ctrlFlag, leftCtrl.reelResult(), rightCtrl.reelResult());
        event.stopCenterReel = true;
    };

    // right reel
    if (inputStates.right == true && rightReel.state == ReelState::Spin && leftReel.state != ReelState::Spin ){
        rightReel.state = ReelState::Wait;
        rightReel.stopSymbolIndex = rightCtrl.secondStopSymbolIndex(rightReel.symbolIndex(), ctrlFlag, leftCtrl.targetSymbolRow(ctrlFlag));
        event.stopRightReel = true;
    }

    // Start spin
    if (dt > GameConst::reelWait && reelsState == ReelState::Wait) {
        startSpin();
        reelsState = ReelState::Spin;
        prevStartSpinTime = now;
        event.startReel = true;
    };

    // Update reel
    leftReel.updateScrollY();
    centerReel.updateScrollY();
    rightReel.updateScrollY();

    // check stop all reel
    if (leftReel.state == ReelState::Stop && centerReel.state == ReelState::Stop && rightReel.state == ReelState::Stop && reelsState == ReelState::Spin) {
        reelsState = ReelState::Stop;
    };
}

void ReelManager::startSpin(){
    leftReel.state = ReelState::Spin;
    centerReel.state =  ReelState::Spin;
    rightReel.state = ReelState::Spin;
};
