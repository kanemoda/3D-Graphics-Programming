#include "vector.h"

//TODO:: Implementation of vector functions
//Orthographic Projection
vec2_t Orthographic_project(vec3_t vec3)
{
    vec2_t vec2 = {
        // in real projection it should be x' = (x/z) * fov_factor and y'= (y/z) * fov_factor
        fov_factor * vec3.x,
        fov_factor * vec3.y
    };
    return vec2;
}

// lets try real projection like prespective?
vec2_t Perspective_project(vec3_t vec3)
{
    vec2_t vec2 = {
        fov_factor * (vec3.x/vec3.z),
        fov_factor * (vec3.y / vec3.z),
    };
    return vec2;
}