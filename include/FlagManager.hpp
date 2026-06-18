#pragma once
#include "toml.hpp"
#include <cstddef>
#include <optional>
#include <string_view>
#include <vector>
#include <random>
#include "ReelManager.hpp"

using namespace std;

struct Flag{
    string name;
    int allocateNum;
    int payout;
    ReelCtrlFlag ctrl;
};

inline const Flag miss{
    .name = "miss",
    .allocateNum = 65536,
    .payout = 0,
    .ctrl = ReelCtrlFlag::Miss
};

vector<Flag> load_flags(const toml::table& tables, string_view key);

class FlagLottery{
private:
    vector<Flag> roleFlags;
    vector<Flag> bonusFlags;
    mt19937 rng{random_device{}()};
    uniform_int_distribution<uint16_t> dist{0, 65535};
    optional<Flag> bonusFlag=nullopt;

    vector<Flag> load_flags(const toml::table& tables, string_view key);

public:
    void init();
    optional<Flag> draw();
};
