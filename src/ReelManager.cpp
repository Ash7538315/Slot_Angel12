#include "ReelManager.hpp"
#include "GameConst.hpp"
#include "InputManager.hpp"
#include "ReelData.hpp"

using namespace std;

void ReelManager::init(){
    leftReel.state = ReelState::Stop;
    leftReel.reelPos = GameConst::symbolHeight * 3 - GameConst::symbolHeight / 12.0;

    centerReel.state = ReelState::Stop;
    centerReel.reelPos = GameConst::symbolHeight * 3 - GameConst::symbolHeight / 12.0;

    rightReel.state = ReelState::Stop;
    rightReel.reelPos = GameConst::symbolHeight * 3 - GameConst::symbolHeight / 12.0;

    reelsState = ReelsState::WaitLever;

    leftReel.init(leftReelStrips, leftSlipTables, leftTargetSymbolTable);
    centerReel.init(centerReelStrips, centerSlipTables, centerTargetSymbolTable);
    rightReel.init(rightReelStrips, rightSlipTables, rightTargetSymbolTable);
};

void ReelManager::update(const InputStates& inputStates, const CtrlFlag& ctrlFlag, const BonusState& bonusState){
    // for Reel Wait
    now = SDL_GetPerformanceCounter();
    double dt = (now - prevStartSpinTime) / freq;

    // left reel
    if ( dt >= GameConst::startWait && inputStates.left && leftReel.state == ReelState::Spin ){
        leftReel.state = ReelState::Wait;
        leftReel.firstStop(ctrlFlag);
    };

    // center reel
    if (inputStates.center && centerReel.state == ReelState::Spin && leftReel.state != ReelState::Spin && rightReel.state != ReelState::Spin ){
        centerReel.state = ReelState::Wait;
        centerReel.thirdStop(ctrlFlag, leftReel.stopSymbols, rightReel.stopSymbols, bonusState);
    };

    // right reel
    if (inputStates.right && rightReel.state == ReelState::Spin && leftReel.state != ReelState::Spin ){
        rightReel.state = ReelState::Wait;
        rightReel.secondStop(ctrlFlag, leftReel.targetRow(ctrlFlag));
    }

    // Start spin
    // Ctrl ReelWait
    if (dt > GameConst::reelWait && reelsState == ReelsState::WaitStart) {
        startSpin();
        reelsState = ReelsState::Spin;
        prevStartSpinTime = now;
        event.startReel = true;
    };

    // Update reel
    leftReel.updateReelPos();
    centerReel.updateReelPos();
    rightReel.updateReelPos();

    // Check Reel stop Now
    if (leftReel.stopNow) {
        event.stopLeftReel = true;
    };
    if (centerReel.stopNow) {
        event.stopCenterReel = true;
    };
    if (rightReel.stopNow) {
        event.stopRightReel = true;
    }

    // check stop all reel
    if (leftReel.state == ReelState::Stop && centerReel.state == ReelState::Stop && rightReel.state == ReelState::Stop && reelsState == ReelsState::Spin) {
        reelsState = ReelsState::Stop;
        switch (bonusState) {
            case BonusState::Bonus:
                reelsResult = check1Line(leftReel.stopSymbols, centerReel.stopSymbols, rightReel.stopSymbols, combinationTableInBonus);
                break;
            default:
                reelsResult = check5Line(leftReel.stopSymbols, centerReel.stopSymbols, rightReel.stopSymbols, combinationTable);
                break;
        }
        
    };
}

void ReelManager::startSpin(){
    leftReel.state = ReelState::Spin;
    centerReel.state =  ReelState::Spin;
    rightReel.state = ReelState::Spin;
};

