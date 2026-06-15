#include "ReelCtrl.hpp"
#include <stdexcept>
#include <string_view>
#include <unordered_map>

using namespace std;

ReelCtrl to_ReelCtrl(string_view str){
    static const unordered_map<string_view, ReelCtrl> table{
        {"suikaA",  ReelCtrl::SuikaA},
        {"suikaB",  ReelCtrl::SuikaB},
        {"cherry",  ReelCtrl::Cherry},
        {"bell",    ReelCtrl::Bell},
        {"replay",  ReelCtrl::Replay},
        {"miss",    ReelCtrl::Miss},
        {"redBB",   ReelCtrl::RedBB},
        {"blueBB",    ReelCtrl::BlueBB},
        {"RB",      ReelCtrl::RB}
    };

    if (auto it = table.find(str); it != table.end())
        return it->second;

    throw runtime_error("Unknown ReelCtrl: " + string(str));
}
