#include "FlagData.hpp"
#include "StateManager.hpp"

Flag StateManager::selectFlag(const span<const Flag> flags){
    int num = dist(rng);
    for (const Flag& flag : flags){
        num -= flag.allocateNum;
        if (num < 0){
            return flag;
        }
    }
    return miss;
};

void StateManager::init(){
    totalGameCount = 0;
    gameCount = 0;
    coin = 0;
    hasBonusFlag = none;
    bonusState = BonusState::Normal;
    isBet = false;
};

void StateManager::bet(){
    isBet = true;

    switch (bonusState) {
        case BonusState::Bonus:
            coin -= 2;
            event.bet = true;
            return;
        default:
            coin -= 3;
            event.bet = true;
            return;
    }
}

void StateManager::drawFlag(){
    switch (bonusState) {
        case BonusState::Bonus:
            currentFlag = selectFlag(roleFlagsInBB);
            break;
        case BonusState::Normal:
            Flag flag = selectFlag(roleFlags);
            if (flag == miss) {
                if (hasBonusFlag == none) {
                    flag = selectFlag(bonusFlags);
                } else {
                    flag = hasBonusFlag;
                }
            };
            currentFlag = flag;
    }
}

void StateManager::evaluateResult(const ResultFlag& reelResult){
    totalGameCount += 1;
    isBet = false;
    switch (bonusState) {
        case BonusState::Bonus:
            for (const Flag& flag : roleFlagsInBB){
                if (reelResult == currentFlag.result) {
                    coin += currentFlag.payout;
                    remainPayput -= currentFlag.payout;
                }
            };
            remainGameCount -= 1;
            // End bonus
            if (remainGameCount <= 0 || remainPayput <= 0){
                bonusState = BonusState::Normal;
                hasBonusFlag = none;
                event.endBonus = true;
            };
            break;

        default:
            gameCount += 1;
            if (reelResult == currentFlag.result) {
                coin += currentFlag.payout;
            }
            if (reelResult == ResultFlag::Replay) {
                isBet = true;
            }

            if (reelResult == ResultFlag::RedBB || reelResult == ResultFlag::BlueBB){
                bonusState = BonusState::Bonus;
                remainPayput = SlotStateConst::MAX_BB_PAYOUT;
                remainGameCount = SlotStateConst::MAX_BB_GAMECOUNT;
                event.startRedBB = true;
            }
            break;
    }
};
