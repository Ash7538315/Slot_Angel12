#include "Reel.hpp"
#include "GameConst.hpp"
#include "ReelData.hpp"
#include <array>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

ReelsResult check5Line(const ColSymbols& leftStopSymbols, const ColSymbols& centerStopSymbols, const ColSymbols& rightStopSymbols, span<const LineResult> table){
    vector<ReelsResult> reelsResults;
    for (const LineResult& combination : table) {
        // top line
        if (leftStopSymbols.top == combination.left && centerStopSymbols.top == combination.center && rightStopSymbols.top == combination.right) {
            reelsResults.push_back({combination.resultFlag, WinningLine::Top});
        };
        // middle line
        if (leftStopSymbols.middle == combination.left && centerStopSymbols.middle == combination.center && rightStopSymbols.middle == combination.right) {
            reelsResults.push_back({combination.resultFlag, WinningLine::Middle});
        };
        // bottom line
        if (leftStopSymbols.bottom == combination.left && centerStopSymbols.bottom == combination.center && rightStopSymbols.bottom == combination.right) {
            reelsResults.push_back({combination.resultFlag, WinningLine::Bottom});
        };
        // top 2 bottom
        if (leftStopSymbols.top == combination.left && centerStopSymbols.middle == combination.center && rightStopSymbols.bottom == combination.right) {
            reelsResults.push_back({combination.resultFlag, WinningLine::Top2Bottom});
        };
        // bottom 2 top
        if (leftStopSymbols.bottom == combination.left && centerStopSymbols.middle == combination.center && rightStopSymbols.top == combination.right) {
            reelsResults.push_back({combination.resultFlag, WinningLine::Bottom2Top});
        };
    }

    switch (reelsResults.size()) {
        case 0:
            return {ResultFlag::Miss, WinningLine::None};
        case 1:
            return reelsResults.front();
        default:
            auto it = find_if(
                reelsResults.begin(), 
                reelsResults.end(), 
                [](const ReelsResult& r){
                    return r.flag == ResultFlag::Cherry;
                });
            if (it != reelsResults.end()){
                return {ResultFlag::BadPattern, WinningLine::None};
            };

            return reelsResults.front();
    }
};

ReelsResult check1Line(const ColSymbols& leftStopSymbols, const ColSymbols& centerStopSymbols, const ColSymbols& rightStopSymbols, span<const LineResult> table){
    vector<ReelsResult> reelsResults;
    for (const LineResult& combination : table) {
        // middle line
        if (leftStopSymbols.middle == combination.left && centerStopSymbols.middle == combination.center && rightStopSymbols.middle == combination.right) {
            reelsResults.push_back({combination.resultFlag, WinningLine::Middle});
        };
    }

    switch (reelsResults.size()) {
        case 0:
            return {ResultFlag::Miss, WinningLine::None};
        case 1:
            return reelsResults.front();
        default:
            auto it = find_if(
                reelsResults.begin(), 
                reelsResults.end(), 
                [](const ReelsResult& r){
                    return r.flag == ResultFlag::Cherry;
                });
            if (it != reelsResults.end()){
                return {ResultFlag::BadPattern, WinningLine::None};
            };

            return reelsResults.front();
    }
};

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
    for (const Symbol& targetSymbol : targetSymbolTable->at(ctrlFlag)) {
        for (const ReelRow& row : reelRows) {
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
            stopNow=false;
            break;
        case ReelState::Spin:
            reelPos -= GameConst::scrollSpeed;
            if (reelPos <= GameConst::symbollHeight - GameConst::symbollHeight / 12.0) {
                reelPos += GameConst::symbollHeight * GameConst::nsymbol;
            }
            stopNow=false;
            break;
        case ReelState::Wait:
            float d = reelPos - stopReelPos(stopPosIndex);
            if (d < 0){
                d += GameConst::symbollHeight * GameConst::nsymbol;
            }

            if (d <= GameConst::scrollSpeed) {
                reelPos = stopReelPos(stopPosIndex);
                state = ReelState::Stop;
                stopNow = true;
            } else {
                reelPos -= GameConst::scrollSpeed;
                if (reelPos <= GameConst::symbollHeight - GameConst::symbollHeight / 12.0) {
                    reelPos += GameConst::symbollHeight * GameConst::nsymbol;
                }
            }
            break;
    }
}

void CenterReel::thirdStop(const CtrlFlag& ctrlFlag, const ColSymbols& leftStopSymbols, const ColSymbols& rightStopSymbols, const BonusState& bonusState){
    vector<int> slipOptions;
    for (const ResultFlag& drawnFlag : ctrlFlag2ResultFlag.at(ctrlFlag)) {
        for (int islip = 0; islip <=4; ++islip){
            int loc = posIndex() - islip;
            if (loc <= 0){
                loc += GameConst::nsymbol;
            };
            ColSymbols centerStopSymbols = colSymbols(loc);
            ReelsResult reelsResult;
            switch (bonusState) {
                case BonusState::Normal:
                    reelsResult = check5Line(leftStopSymbols, centerStopSymbols, rightStopSymbols, combinationTable);
                    break;
                case BonusState::Bonus:
                    reelsResult= check1Line(leftStopSymbols, centerStopSymbols, rightStopSymbols, combinationTableInBonus);
                    break;
            }
            
            if (reelsResult.flag == drawnFlag){
                slipOptions.push_back(islip);
            }
        };
    }

    if (slipOptions.empty()) {
        cerr << "Not Found third Stop Pattern" << endl;
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
