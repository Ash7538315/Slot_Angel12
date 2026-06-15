#include <fstream>
#include <iostream>
#include <string_view>
#include "toml.hpp" 
#include "FlagLottery.hpp"


using namespace std;


int main(){
    // init
    ifstream flag_tables("../asset/config/flag_table.toml");
    auto tomlTable = toml::parse(flag_tables);
    vector<Flag> roleFlags = load_flags(tomlTable, "role_flag");
    vector<Flag> bonusFlags = load_flags(tomlTable, "bonus_flag");

    FlagLottery flagDrawer(roleFlags, bonusFlags);

    
    while (true) {
        cout<< flagDrawer.draw()->name << endl;
        cin.get();
    }
}
