#include "FlagLottery.hpp"
#include "ReelCtrl.hpp"
#include <string_view>

vector<Flag> load_flags(const toml::table& tables, string_view key){
    vector<Flag> flags;
    auto arr = tables[key].as_array();
    for (const auto& node : *arr){
        auto table = node.as_table();

        Flag flag;
        flag.name = table->at("name").value<string_view>().value();
        flag.payout = table->at("payout").value<int>().value();
        flag.allocateNum = table->at("allocateNum").value<int>().value();
        flag.ctrl = to_ReelCtrl(table->at("ctrl").value<string_view>().value());

        flags.push_back(std::move(flag));
    }
    return flags;
}

optional<Flag> FlagLottery::draw(){
    int num = dist(rng);
    for (const auto& flag : roleFlags){
        num -= flag.allocateNum;
        if (num < 0){
            return flag;
        }
    }

    if (!bonusFlag){
    for (const auto& flag : bonusFlags){
        num -= flag.allocateNum;
        if (num < 0){
            bonusFlag = flag;
            return flag;
        }
    }
    }
    
    if (bonusFlag) {
        return bonusFlag;
    }

    return miss;
    //nullopt
}
