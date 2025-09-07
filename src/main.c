#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <errno.h>
#include <string.h>

//Global vars
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool is_running = false;
uint32_t* color_buffer = NULL;

int window_width = 800;
int window_height = 600;

bool initialize_window(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return false;
    }
    // Create a SDL Window
    window = SDL_CreateWindow(
        NULL, 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED,
        window_width,
        window_height,
        SDL_WINDOW_BORDERLESS        
    );

    if (!window)
    {
        fprintf(stderr, "Error creating SDL window: %s\n", SDL_GetError());
        return false;
    }

    // Create a SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        fprintf(stderr, "Error creating SDL renderer: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void setup(void)
{
    if (window_width == 0 || window_height == 0)
    {
        fprintf(stderr, "Invalid window size: %s\n", strerror(errno));
        is_running = false;
        return;
    }
    
    color_buffer = malloc(sizeof(uint32_t) * window_width *window_height);

    if (!color_buffer)
    {
        fprintf(stderr, "color_buffer allocaation failed: %s\n", strerror(errno));
        is_running = false;
    }
    
}

void process_input(void)
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
        case SDL_QUIT:
            is_running = false;
            break; 
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    is_running = false;
                }
                break;
    }
}

void update (void)
{
    //TODO:
}

void render(void)
{
    SDL_SetRenderDrawColor(renderer, 255 ,0 ,0 ,255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}

void destroy_window(void)
{
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(void)
{
    is_running = initialize_window();
    
    setup();

    while (is_running)
    {
        process_input();
        update();
        render();
    }

    destroy_window();
    

    return 0;
}