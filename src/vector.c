#include "vector.h"

//TODO:: Implementation of vector functions
//Orthographic Projection
vec2_t project(vec3_t vec3)
{
    vec2_t vec2 = {
        FOV_FACTOR * vec3.x,
        FOV_FACTOR * vec3.y
    };
    return vec2;
}