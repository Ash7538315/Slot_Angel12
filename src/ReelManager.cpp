#include "ReelManager.hpp"
#include "GameConst.hpp"
#include "InputManager.hpp"
#include "toml.hpp"
#include <limits>
#include <stdexcept>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <cmath>

using namespace std;

ReelCtrlFlag to_ReelCtrlFlag(string_view str){
    static const unordered_map<string_view, ReelCtrlFlag> table{
        {"suikaA",  ReelCtrlFlag::SuikaA},
        {"suikaB",  ReelCtrlFlag::SuikaB},
        {"cherry",  ReelCtrlFlag::Cherry},
        {"bell",    ReelCtrlFlag::Bell},
        {"replay",  ReelCtrlFlag::Replay},
        {"miss",    ReelCtrlFlag::Miss},
        {"redBB",   ReelCtrlFlag::RedBB},
        {"blueBB",    ReelCtrlFlag::BlueBB},
        {"RB",      ReelCtrlFlag::RB}
    };

    if (auto it = table.find(str); it != table.end())
        return it->second;

    throw runtime_error("Unknown ReelCtrlFlag: " + string(str));
}

float Reel::stopScrollY(const int& symbolIndex){
    float scrollY = (symbolIndex + 2) * GameConst::symbollHeight - GameConst::symbollHeight / 12.0;
    if (scrollY > GameConst::symbollHeight * GameConst::nsymbol){
        scrollY -= GameConst::symbollHeight * GameConst::nsymbol;
    }; 
    return scrollY;
};

int Reel::symbolIndex(){
    int symbolIndex = floor((reelScrollY + GameConst::symbollHeight / 12.0) / GameConst::symbollHeight - 2);
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
            if (dscrollY >= GameConst::symbollHeight * GameConst::nsymbol){
                dscrollY -= GameConst::symbollHeight * GameConst::nsymbol;
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

void ReelCtrl::init(){};

int ReelCtrl::calcStopSymbolIndex(int symbolindex, ReelCtrlFlag reelCtrlFlag){
    switch (reelCtrlFlag) {
        case ReelCtrlFlag::Unctrl:
            return symbolindex;
        default:
            return symbolindex;
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
};
void ReelManager::ctrl(const InputStates& inputStates){
    // if (reelsState == ReelState::Stop && inputStates.lever == true) {
    //     startSpin();
    //     reelsState = ReelState::Spin;
    // }

    if (inputStates.lever == true) {
        startSpin();
        reelsState = ReelState::Spin;
    }

    if (inputStates.left == true && leftReel.state == ReelState::Spin ){
        leftReel.state = ReelState::Wait;
        leftReel.stopSymbolIndex = leftCtrl.calcStopSymbolIndex(leftReel.symbolIndex(), ReelCtrlFlag::Unctrl);
    }


    // Update reel
    leftReel.updateScrollY();
    centerReel.updateScrollY();
    rightReel.updateScrollY();
};

void ReelManager::startSpin(){
    leftReel.state = ReelState::Spin;
    centerReel.state =  ReelState::Spin;
    rightReel.state = ReelState::Spin;
};
