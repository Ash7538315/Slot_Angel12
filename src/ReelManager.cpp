#include "ReelManager.hpp"
#include "GameConst.hpp"
#include "InputManager.hpp"
#include "ReelData.hpp"
#include <array>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

void Reel::init(const array<Symbol, 21>& ReelStrips, const map<CtrlFlag, SlipTable>& SlipTable, const map<CtrlFlag, vector<Symbol>>& TargetSymbolTable){
    reelStrips = &ReelStrips;
    slipTable = &SlipTable;
    targetSymbolTable = &TargetSymbolTable;
};

void Reel::firstStop(const CtrlFlag& ctrlFlag){
    stopPosIndex = posIndex() - slipTable->at(ctrlFlag)[posIndex() - 1];

    if (stopPosIndex <= 0) {
        stopPosIndex += GameConst::nsymbol;
    }
    stopSymbols = colSymbols(stopPosIndex);
};

ReelRow Reel::targetRow(const CtrlFlag& ctrlFlag){
    for (const ReelRow& row : reelRows) {
        for (const Symbol& targetSymbol : targetSymbolTable->at(ctrlFlag)) {
            if((*reelStrips)[stopPosIndex+static_cast<int>(row)-1] == targetSymbol){
                return row;
            };
        }
    };

    if (ctrlFlag == CtrlFlag::RedBB || ctrlFlag == CtrlFlag::RB) {
        return ReelRow::Bottom;;
    }

    return ReelRow::None;;
};

ColSymbols Reel::colSymbols(const int& posIndex){
    int i = posIndex;
    int j= posIndex + 1;
    int k= posIndex + 2;

    if (j > GameConst::nsymbol){
        j -= GameConst::nsymbol;
    };

    if (k > GameConst::nsymbol){
        k -= GameConst::nsymbol;
    };

    ColSymbols colSymbols = {
        .top = (*reelStrips)[i-1],
        .middle = (*reelStrips)[j-1],
        .bottom = (*reelStrips)[k-1],
    };
    return colSymbols;
};

float Reel::stopReelPos(const int& symbolIndex){
    float reelPos = (symbolIndex + 2) * GameConst::symbollHeight - GameConst::symbollHeight / 12.0;
    if (reelPos > GameConst::symbollHeight * GameConst::nsymbol - GameConst::symbollHeight / 12.0){
        reelPos -= GameConst::symbollHeight * GameConst::nsymbol;
    }; 
    return reelPos;
};

int Reel::posIndex(){
    int symbolIndex = floor((reelPos + GameConst::symbollHeight / 12.0) / GameConst::symbollHeight) - 2;
    if (symbolIndex <= 0) {
        symbolIndex += GameConst::nsymbol;
    }
    return symbolIndex;
};

void Reel::updateReelPos(){
    switch (state) {
        case ReelState::Stop:
            break;
        case ReelState::Spin:
            reelPos -= GameConst::scrollSpeed;
            if (reelPos <= GameConst::symbollHeight - GameConst::symbollHeight / 12.0) {
                reelPos += GameConst::symbollHeight * GameConst::nsymbol;
            }
            break;
        case ReelState::Wait:
            float d = reelPos - stopReelPos(stopPosIndex);
            if (d < 0){
                d += GameConst::symbollHeight * GameConst::nsymbol;
            }

            if (d <= GameConst::scrollSpeed) {
                reelPos = stopReelPos(stopPosIndex);
                state = ReelState::Stop;
            } else {
                reelPos -= GameConst::scrollSpeed;
                if (reelPos <= GameConst::symbollHeight - GameConst::symbollHeight / 12.0) {
                    reelPos += GameConst::symbollHeight * GameConst::nsymbol;
                }
            }
            break;
    }
}

void CenterReel::thirdStop(const CtrlFlag& ctrlFlag, const ColSymbols& leftStopSymbols, const ColSymbols& rightStopSymbols){
    vector<int> slipOptions;
    for (const ResultFlag& drawnFlag : ctrlFlag2ResultFlag.at(ctrlFlag)) {
        for (int islip = 0; islip <=4; ++islip){
            int loc = posIndex() - islip;
            if (loc <= 0){
                loc += GameConst::nsymbol;
            };
            ColSymbols centerStopSymbols = colSymbols(loc);
            ResultFlag resultFlags= check5Line(leftStopSymbols, centerStopSymbols, rightStopSymbols, combinationTable);
            if (resultFlags == drawnFlag){
                slipOptions.push_back(islip);
            }
        };
    }

    if (slipOptions.empty()) {
        cerr << "Not Found second Stop Pattern" << endl;
        stopPosIndex = posIndex();
    }
 
    stopPosIndex = posIndex() - slipOptions[0];
    if (stopPosIndex <= 0){
        stopPosIndex += GameConst::nsymbol;
    };
    stopSymbols = colSymbols(stopPosIndex);
};

void RightReel::secondStop(const CtrlFlag& ctrlFlag, const ReelRow& leftTargetSymbolRow){
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
                int loc = posIndex() - islip + static_cast<int>(row);
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
        stopPosIndex = posIndex(); 
    }

    // Ctrl linetype
    stopPosIndex= posIndex() - slipOptions[0].slipNum;
    if (ctrlFlag == CtrlFlag::SuikaB || ctrlFlag == CtrlFlag::RedBB || ctrlFlag == CtrlFlag::RB) {
        for (const SlipOptions& option : slipOptions) {
            if (option.type == LineType::Diagonal) {
                stopPosIndex = posIndex() - option.slipNum;
                break;
            }
        }
    }

    if (ctrlFlag == CtrlFlag::SuikaA) {
        for (const SlipOptions& option : slipOptions) {
            if (option.type == LineType::Horizontal) {
                stopPosIndex = posIndex() - option.slipNum;
                break;
            }
        }
    }

    if (stopPosIndex<= 0) {
        stopPosIndex += GameConst::nsymbol;
    }

    stopSymbols = colSymbols(stopPosIndex);
};

void ReelManager::init(){
    leftReel.state = ReelState::Stop;
    leftReel.reelPos = GameConst::symbollHeight * 3 - GameConst::symbollHeight / 12.0;

    centerReel.state = ReelState::Stop;
    centerReel.reelPos = GameConst::symbollHeight * 3 - GameConst::symbollHeight / 12.0;

    rightReel.state = ReelState::Stop;
    rightReel.reelPos = GameConst::symbollHeight * 3 - GameConst::symbollHeight / 12.0;

    reelsState = ReelState::Stop;

    leftReel.init(leftReelStrips, leftSlipTables, leftTargetSymbolTable);
    centerReel.init(centerReelStrips, centerSlipTables, centerTargetSymbolTable);
    rightReel.init(rightReelStrips, rightSlipTables, rightTargetSymbolTable);
};

void ReelManager::ctrl(const InputStates& inputStates, const CtrlFlag& ctrlFlag, const BonusStates& bonusState){
    event.clear();

    // for Reel Wait
    now = SDL_GetPerformanceCounter();
    double dt = (now - prevStartSpinTime) / freq;

    // Lever on
    if (reelsState == ReelState::Stop && inputStates.lever == true) {
        reelsState = ReelState::Wait;
    }

    // left reel
    if ( dt >= GameConst::startWait && inputStates.left == true && leftReel.state == ReelState::Spin ){
        leftReel.state = ReelState::Wait;
        leftReel.firstStop(ctrlFlag);
        event.stopLeftReel = true;
    };

    // center reel
    if (inputStates.center == true && centerReel.state == ReelState::Spin && leftReel.state != ReelState::Spin && rightReel.state != ReelState::Spin ){
        centerReel.state = ReelState::Wait;
        centerReel.thirdStop(ctrlFlag, leftReel.stopSymbols, rightReel.stopSymbols);
        event.stopCenterReel = true;
    };

    // right reel
    if (inputStates.right == true && rightReel.state == ReelState::Spin && leftReel.state != ReelState::Spin ){
        rightReel.state = ReelState::Wait;
        rightReel.secondStop(ctrlFlag, leftReel.targetRow(ctrlFlag));
        event.stopRightReel = true;
    }

    // Start spin
    // Ctrl ReelWait
    if (dt > GameConst::reelWait && reelsState == ReelState::Wait) {
        startSpin();
        reelsState = ReelState::Spin;
        prevStartSpinTime = now;
        event.startReel = true;
    };

    // Update reel
    leftReel.updateReelPos();
    centerReel.updateReelPos();
    rightReel.updateReelPos();

    // check stop all reel
    if (leftReel.state == ReelState::Stop && centerReel.state == ReelState::Stop && rightReel.state == ReelState::Stop && reelsState == ReelState::Spin) {
        reelsState = ReelState::Stop;
        reelResult = check5Line(leftReel.stopSymbols, centerReel.stopSymbols, rightReel.stopSymbols, combinationTable);
    };
}

void ReelManager::startSpin(){
    leftReel.state = ReelState::Spin;
    centerReel.state =  ReelState::Spin;
    rightReel.state = ReelState::Spin;
};

ResultFlag check5Line(const ColSymbols& leftStopSymbols, const ColSymbols& centerStopSymbols, const ColSymbols& rightStopSymbols, span<const LineResult> table){
    vector<ResultFlag> resultFlags;
    for (const LineResult& combination : table) {
        // top line
        if (leftStopSymbols.top == combination.left && centerStopSymbols.top == combination.center && rightStopSymbols.top == combination.right) {
            resultFlags.push_back(combination.resultFlag);
        };
        // middle line
        if (leftStopSymbols.middle == combination.left && centerStopSymbols.middle == combination.center && rightStopSymbols.middle == combination.right) {
            resultFlags.push_back(combination.resultFlag);
        };
        // bottom line
        if (leftStopSymbols.bottom == combination.left && centerStopSymbols.bottom == combination.center && rightStopSymbols.bottom == combination.right) {
            resultFlags.push_back(combination.resultFlag);
        };
        // top 2 bottom
        if (leftStopSymbols.top == combination.left && centerStopSymbols.middle == combination.center && rightStopSymbols.bottom == combination.right) {
            resultFlags.push_back(combination.resultFlag);
        };
        // bottom 2 top
        if (leftStopSymbols.bottom == combination.left && centerStopSymbols.middle == combination.center && rightStopSymbols.top == combination.right) {
            resultFlags.push_back(combination.resultFlag);
        };
    }

    switch (resultFlags.size()) {
        case 0:
            return ResultFlag::Miss;
        case 1:
            return resultFlags[0];
        default:
            return ResultFlag::BadPattern;
    }

};

ResultFlag check1Line(const ColSymbols& leftStopSymbols, const ColSymbols& centerStopSymbols, const ColSymbols& rightStopSymbols, span<const LineResult> table){
    vector<ResultFlag> resultFlags;
    for (const LineResult& combination : table) {
        // middle line
        if (leftStopSymbols.middle == combination.left && centerStopSymbols.middle == combination.center && rightStopSymbols.middle == combination.right) {
            resultFlags.push_back(combination.resultFlag);
        };
    }

    switch (resultFlags.size()) {
        case 0:
            return ResultFlag::Miss;
        case 1:
            return resultFlags[0];
        default:
            return ResultFlag::BadPattern;
    }
};
