
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
                    case SDLK_RCTRL:
                        inputStates.lever = true;
                        break;
                    case SDLK_LCTRL:
                        inputStates.lever = true;
                        break;
                    case SDLK_A:
                        inputStates.left = true;
                        break;
                    case SDLK_LEFT:
                        inputStates.left = true;
                        break;
                    case SDLK_S:
                        inputStates.center = true;
                        break;
                    case SDLK_DOWN:
                        inputStates.center = true;
                        break;
                    case SDLK_D:
                        inputStates.right = true;
                        break;
                    case SDLK_RIGHT:
                        inputStates.right = true;
                        break;
                    case SDLK_B:
                        inputStates.bet = true;
                        break;
                    case SDLK_LSHIFT:
                        inputStates.bet = true;
                        break;
                    case SDLK_RSHIFT:
                        inputStates.bet = true;
                        break;
                };       
        }
    }
}
