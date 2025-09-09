#ifndef DISPLAY_H
#define DISPLAY_H

#include "globals.h"
#include <math.h>
#include <stdbool.h>
#include "utils.h"


bool initialize_window(void);
void draw_grid(void);
void draw_grid_fast(int step, uint32_t color);
void draw_grid_GPU(int step, SDL_Color c);
void draw_rect(uint32_t color, int x1 , int y1, int x2, int y2);
void render_color_buffer(void);
void clear_color_buffer(uint32_t color);
void dvd_animation(uint32_t color);
void destroy_window(void);
uint32_t rainbow_color(void);

#endif //DISPLAY_H