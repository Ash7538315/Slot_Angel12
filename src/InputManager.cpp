
#include "InputManager.hpp"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_keycode.h"

void InputManager::clear(){
    inputStates ={};
}
void InputManager::check(){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                inputStates.quit = true;
                break;
            case SDL_EVENT_KEY_DOWN:
                switch (event.key.key) {
                    case SDLK_RETURN:
                        inputStates.lever = true;
                        break;
                    case SDLK_UP:
                        inputStates.lever = true;
                        break;
                    case SDLK_W:
                        inputStates.lever = true;
                        break;
                    case SDLK_A:
                        inputStates.left = true;
                        break;
                    case SDLK_LEFT:
                        inputStates.left = true;
                        break;
                };
                
        }

    }
}
