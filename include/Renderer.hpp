#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

class Renderer{
private:
    static SDL_Window* window;
    // static SDL_Renderer *renderer;
public:
    void init();
    void run();
    void exit();
};
