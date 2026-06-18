#include "ReelCtrl.hpp"
#include "GameConst.hpp"
#include <stdexcept>
#include <string_view>
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

void ReelCtrl::init(){};
void ReelCtrl::leftCtrl(){
    leftReel.ReelScrollY -= GameConst::scrollSpeed;
    if (leftReel.ReelScrollY < 121){
        leftReel.ReelScrollY += GameConst::symbollHeight * GameConst::nsymbol;
    }
};

int Reel::symbolIndex(){
    return ReelScrollY / GameConst::symbollHeight + 1;
};
