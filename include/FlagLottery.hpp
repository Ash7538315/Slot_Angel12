#pragma once
#include "toml.hpp"
#include <cstddef>
#include <optional>
#include <string_view>
#include <vector>
#include <random>
#include "ReelCtrl.hpp"

using namespace std;

struct Flag{
    string_view name;
    int allocateNum;
    int payout;
    ReelCtrl ctrl;
};

inline const Flag miss{
    .name = "miss",
    .allocateNum = 65536,
    .payout = 0,
    .ctrl = ReelCtrl::Miss
};

vector<Flag> load_flags(const toml::table& tables, string_view key);

class FlagLottery{
private:
    const vector<Flag>& roleFlags;
    const vector<Flag>& bonusFlags;
    mt19937 rng{random_device{}()};
    uniform_int_distribution<uint16_t> dist{0, 65535};

    optional<Flag> bonusFlag;

public:
    FlagLottery(vector<Flag>& roleFlags, vector<Flag>& bonusFlags):
        roleFlags(roleFlags),
        bonusFlags(bonusFlags)
        {}
    optional<Flag> draw();
};
