#include "Reel_new.hpp"
#include "GameConst.hpp"
#include "ReelData.hpp"
#include <array>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int Reel::calcPosIndex(){
    return ceil((reelPos + GameConst::SymbolMargin) / GameConst::symbolHeight);
}

void Reel::init(
        const array<Symbol, ReelConst::nsymbol>& strips, 
        const array<SlipTable, ReelConst::nCtrlFlag>& slipTable, 
        const array<vector<Symbol>, ReelConst::nCtrlFlag>& targetSymTable
    )
{
    reelStrips = &strips;
    firstSlipTable = &slipTable;
    targetSymbolTable = &targetSymTable;
};

void Reel::firstStop(const CtrlFlag& ctrlFlag){
    int posIndex = calcPosIndex();
    int stopPosIndex = calcPosIndex() - (*firstSlipTable)[static_cast<int>(ctrlFlag)][posIndex];
    stopPosIndex = (stopPosIndex + ReelConst::nsymbol) % ReelConst::nsymbol;
    stopReelPos = (stopPosIndex + 1) * GameConst::symbolHeight - GameConst::SymbolMargin;
    stopColSymbols = calcColSymbols(stopPosIndex);
    state = ReelState::WaitStop;
};

void Reel::update(){
    switch (state) {
        case ReelState::Stop:
            break;
        case ReelState::Spin:
            reelPos -= GameConst::scrollSpeed;
            if (reelPos < GameConst::symbolHeight - GameConst::SymbolMargin){
                reelPos += GameConst::symbolHeight * ReelConst::nsymbol;
            };
            break;
        case ReelState::WaitStop:
            reelPos -= GameConst::scrollSpeed;
            if (reelPos < GameConst::symbolHeight - GameConst::SymbolMargin){
                reelPos += GameConst::symbolHeight * ReelConst::nsymbol;
            };
            break;
    }   
};



