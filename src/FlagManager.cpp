#include "FlagData.hpp"
#include "FlagManager.hpp"

void FlagManager::init(){
    hasBonusFlag = miss;
    bonusState = BonusStates::NotBonus;
};

void FlagManager::draw(){
    int num = dist(rng);
    for (const Flag& flag : roleFlags){
        num -= flag.allocateNum;
        if (num < 0){
            currentFlag = flag;
            return;
        }
    }

    if (bonusState == BonusStates::NotBonus){
        for (const Flag& flag : bonusFlags){
            num -= flag.allocateNum;
            if (num < 0){
                currentFlag = flag;
                hasBonusFlag = flag;
                bonusState = BonusStates::HasBonus;
                return;
            }
        }
    }
    
    if (bonusState == BonusStates::HasBonus) {
        currentFlag = hasBonusFlag;
        return;
    }

    currentFlag = miss;
    return;
}
