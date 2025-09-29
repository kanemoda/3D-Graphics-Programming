#include "utils.h"
#include "globals.h"
#include "display.h"
#include "vector.h"


#define N_POINTS  (9*9*9)
vect3_t cube_points[N_POINTS];

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

    if (!color_buffer_texture) {
        fprintf(stderr, "CreateTexture failed: %s\n", SDL_GetError());
        free(color_buffer);
        color_buffer = NULL;
        is_running = false;
        return;
    }
    

    //Load array of vectors
    int point_count = 0;
    for (float  i = -1; i <= 1; i += 0.25)
    {
        for (float j = -1; j <= 1; j += 0.25)
        {
            for (float k = -1; k <= 1; k += 0.25)
            {
                vect3_t new_point = {i,j,k};
                cube_points[point_count++] = new_point;
            }
            
        }
        
    }
    
}

void render(void)
{    
    uint32_t color = rainbow_color();
    clear_color_buffer(color);
    //draw_grid_fast(10,0xFF000000);
    draw_pixel(20,20,0xFFFFFFFF);
    dvd_animation(0xFF000000);
    render_color_buffer();
    SDL_RenderPresent(renderer);
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