#include "utils.h"
#include "globals.h"
#include <SDL2/SDL.h>


void sleep_ms(int ms)
{
    if (ms <= 0) return;
    Uint64 start = SDL_GetTicks64();
    SDL_Event e;

    while (is_running && (int)(SDL_GetTicks64() - start) < ms) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                is_running = false;
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                is_running = false;
            } else {
                SDL_PushEvent(&e); // preserve other inputs for main loop
            }
        }
        SDL_Delay(0); // yield; wake immediately on new events
    }
}

int wrap(int v, int max)
{
    if (max <= 0)
    {
        return 0;
    }
    
    if (v < 0)
    {
        v = max + (v % max);
    }
    return v % max;
    
}