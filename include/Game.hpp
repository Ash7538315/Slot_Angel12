#pragma once
#include <filesystem>
#include <string>

using namespace std;
namespace fs = filesystem;

struct GameConst{
    static inline const char* windowTitle = "Angel12";
    static inline const fs::path rootPath = PROJECT_ROOT;
};

class Game{
private:
public:
    void init();
    void run();
};
