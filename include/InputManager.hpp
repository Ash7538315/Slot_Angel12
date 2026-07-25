#pragma once
struct InputStates{
    bool quit = false;
    bool lever = false;
    bool left = false;
    bool center = false;
    bool right = false;
    bool bet = false;
};

class InputManager{
private:
    InputStates inputStates;

public:
    void clear();
    void check();
    
    const InputStates& state() const{return inputStates;}
};
