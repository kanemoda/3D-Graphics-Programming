#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <errno.h>
#include <string.h>
#include <math.h>

//Global vars
bool is_running = false;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;

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
        SDL_WINDOW_RESIZABLE      
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
    //Allocate memory to hold color buffer
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

    //Create a SDL texture that is used to display color buffer
    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );

    if (!color_buffer_texture)
    {
        fprintf(stderr, "CreateTexture failed: %s\n",SDL_GetError());
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

void sleep(int ms)
{
    uint32_t start = SDL_GetTicks();
    
    while (SDL_GetTicks() - start < ms && is_running)
    {
        process_input();
    }
    
    
}

void render_color_buffer(void)
{
    SDL_UpdateTexture(
        color_buffer_texture,
        NULL,
        color_buffer,
        window_width * sizeof(uint32_t)
    );
    SDL_RenderCopy(
        renderer,
        color_buffer_texture,
        NULL,
        NULL
    );
}

void clear_color_buffer(uint32_t color)
{
    for (int i = 0; i < window_height; i++)
    {
        for (int j = 0; j < window_width; j++)
        {
            color_buffer[(window_width * i) + j] = color;
        }
        
    }
    
}



void render(void)
{
    
    static float time = 0.0f;

    uint8_t r = (uint8_t)(128 + 127 * sin(time + 0.0f));
    uint8_t g = (uint8_t)(128 + 127 * sin(time + 2.094f));
    uint8_t b = (uint8_t)(128 + 127 * sin(time + 4.188f));

    uint32_t color = 0xFF000000 | (r << 16) | (g << 8) | b;

    clear_color_buffer(color);
    render_color_buffer();

    SDL_RenderPresent(renderer);
    time += 0.001f;
    
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