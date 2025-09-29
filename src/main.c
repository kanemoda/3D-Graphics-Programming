#include "utils.h"
#include "globals.h"
#include "display.h"
#include "vector.h"


#define N_POINTS  (9*9*9)
vec3_t cube_points[N_POINTS];
vec2_t projected_points[N_POINTS];

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
    for (int i = 0; i < N_POINTS; i++)
    {
        vec3_t vec3 = cube_points[i];

        vec2_t vec2 = project(vec3);

        projected_points[i] = vec2;
    }
    
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
                vec3_t new_point = {i,j,k};
                cube_points[point_count++] = new_point;
            }
            
        }
        
    }
    
}

void render(void)
{    
    uint32_t bgc = rainbow_color();
    clear_color_buffer(bgc);

    draw_grid_fast(10, 0xFF0F0F0F);
    

    

    for (int i = 0; i < N_POINTS; i++)
    {
        vec2_t vec2 = projected_points[i];
        draw_rect(
            0xFFFFFF00,
            vec2.x + (window_width / 2),
            vec2.y + (window_height / 2),
            vec2.x + (window_width / 2) + 4,
            vec2.y + (window_height / 2) + 4
        );
    }
    

    render_color_buffer();
    clear_color_buffer(0xFF000000);
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