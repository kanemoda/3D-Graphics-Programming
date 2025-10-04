#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "vector.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


extern bool is_running;
extern SDL_Window* window;
extern SDL_Renderer* renderer; 
extern uint32_t* color_buffer;
extern SDL_Texture* color_buffer_texture;
extern int window_width;
extern int window_height;
extern float fov_factor;
extern vec3_t cube_rotation;
extern vec3_t cube_rotation_speed;



#endif //GLOBALS_H