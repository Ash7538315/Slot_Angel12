
#include "InputManager.hpp"
#include "SDL3/SDL_events.h"

void InputManager::clear(){
    inputStates ={};
}
void InputManager::check(){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                inputStates.quit = true;
            case SDL_EVENT_KEY_DOWN:
                inputStates.lever = true;
        }

    }
}
