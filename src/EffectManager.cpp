#include "GameConst.hpp"
#include "EffectManager.hpp"
#include <iostream>

void EffectManager::init(){
    bool isFlash = false;
    double remainFlashTime = 0;
};

void EffectManager::checkFlash(const ReelsResult reelsResult){
    switch (reelsResult.line) {
        case WinningLine::None:
            return;
        case WinningLine::Top:
            event.flash.leftFlashPos = GameConst::symbollHeight / 12.0;
            event.flash.centerFlashPos = GameConst::symbollHeight / 12.0;
            event.flash.rightFlashPos = GameConst::symbollHeight / 12.0;
            break;
        case WinningLine::Middle:
            event.flash.leftFlashPos = GameConst::symbollHeight + GameConst::symbollHeight / 12.0;
            event.flash.centerFlashPos = GameConst::symbollHeight + GameConst::symbollHeight / 12.0;
            event.flash.rightFlashPos = GameConst::symbollHeight + GameConst::symbollHeight / 12.0;
            break;
        case WinningLine::Bottom:
            event.flash.leftFlashPos = GameConst::symbollHeight * 2 + GameConst::symbollHeight / 12.0;
            event.flash.centerFlashPos = GameConst::symbollHeight * 2 + GameConst::symbollHeight / 12.0;
            event.flash.rightFlashPos = GameConst::symbollHeight * 2 + GameConst::symbollHeight / 12.0;
            break;
        case WinningLine::Top2Bottom:
            event.flash.leftFlashPos = GameConst::symbollHeight / 12.0;
            event.flash.centerFlashPos = GameConst::symbollHeight + GameConst::symbollHeight / 12.0;
            event.flash.rightFlashPos = GameConst::symbollHeight * 2 + GameConst::symbollHeight / 12.0;
            break;
        case WinningLine::Bottom2Top:
            event.flash.leftFlashPos = GameConst::symbollHeight * 2 + GameConst::symbollHeight / 12.0;
            event.flash.centerFlashPos = GameConst::symbollHeight + GameConst::symbollHeight / 12.0;
            event.flash.rightFlashPos = GameConst::symbollHeight / 12.0;
            break;
    }
    bool isFlash = true;
    event.flash.isFlash = true;
    double flashTime = 0;
};

void EffectManager::updateFlash(const double& dt, const ReelEvent& reelEvent){
    // std::cout << std::boolalpha
    //           << "isFlash=" << isFlash
    //           << " startReel=" << reelEvent.startReel
    //           << std::endl;

    // if (!isFlash){return;}
    flashTime += dt;
    if (reelEvent.startReel){
        isFlash = false;
        event.flash.isFlash = false;
    }
};
