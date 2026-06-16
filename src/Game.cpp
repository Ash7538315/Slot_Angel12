#include <fstream>
#include <iostream>
#include "FlagLottery.hpp"
#include "Renderer.hpp"
#include "toml.hpp"
#include "Game.hpp"

using namespace std;

void Game::init(){

    FlagLottery flagDrawer;
    flagDrawer.init();

    Renderer renderer;
    renderer.init();

};

void Game::run(){
    cout << "running" << endl;
};
