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
    int stopSymbolIndex = symbolIndex - slipTable->at(ctrlFlag)[symbolIndex-1];

    if (stopSymbolIndex <= 0) {
        stopSymbolIndex += GameConst::nsymbol;
    }
    return stopSymbolIndex;
};

ReelRow ReelCtrl::targetSymbolRow(const int& stopSymbolIndex, const CtrlFlag& ctrlFlag){
    for (ReelRow row : reelRows) {
        for ( Symbol targetSymbol : targetSymbolTable->at(ctrlFlag)) {
            if((*reelStrips)[stopSymbolIndex+static_cast<int>(row)-1] == targetSymbol){
                return row;
            };
        }
    };
    return ReelRow::None;;
};

ReelResult ReelCtrl::reelResult(const int& stopSymbolIndex){
    int i = stopSymbolIndex;
    int j= stopSymbolIndex + 1;
    int k= stopSymbolIndex + 2;

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
    vector<SlipOptions> slipOptions;
    for (int islip = 0; islip <=4; ++islip){
        int loc = symbolIndex - islip;
        if (loc <= 0){
            loc += GameConst::nsymbol;
        };
        ReelResult CenterReelResult = reelResult(loc);
    };
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
    for (Symbol symbol : targetSymbolTable->at(ctrlFlag)){
        for (int islip = 0; islip <=4; ++islip){
            for (ReelRow row : stopRowOptions){
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
    int stopSymbolIndex;
    if (slipOptions.empty()) {
        cerr << "Not Found second Stop Pattern" << endl;
        stopSymbolIndex = symbolIndex; 
    }

    // suika Nado
    stopSymbolIndex = symbolIndex - slipOptions[0].slipNum;

    if (stopSymbolIndex <= 0) {
        stopSymbolIndex += GameConst::nsymbol;
    }
    cerr << "SlipOptions_size: " << slipOptions.size()<< endl;
    return stopSymbolIndex;
};

ResultFlag ReelCtrl::checkResultFlag(const ReelResult& leftReelResult, const ReelResult& centerReelResult, const ReelResult& rightReelResult){
    vector<ResultFlag> resultFlags;
    for (Li)
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
    if (inputStates.center == true && centerReel.state == ReelState::Spin && leftReel.state != ReelState::Spin ){
        centerReel.state = ReelState::Wait;
        centerReel.stopSymbolIndex = centerReel.symbolIndex();
        // centerReel.stopSymbolIndex = centerCtrl.thirdSymbolIndex(centerReel.symbolIndex(), ctrlFlag);
        event.stopCenterReel = true;
    };

    // right reel
    if (inputStates.right == true && rightReel.state == ReelState::Spin && leftReel.state != ReelState::Spin ){
        rightReel.state = ReelState::Wait;
        rightReel.stopSymbolIndex = rightCtrl.secondStopSymbolIndex(rightReel.symbolIndex(), ctrlFlag, leftCtrl.targetSymbolRow(leftReel.stopSymbolIndex, ctrlFlag));
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
