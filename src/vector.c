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
        fov_factor * (vec3.x / vec3.z),
        fov_factor * (vec3.y / vec3.z),
    };
    return vec2;
}

//Rotation Function for x-axis
vec3_t vec3_rotate_x(vec3_t vec, float angle)
{
    vec3_t vec3 = {
        .x = vec.x,
        .y = vec.y * cos(angle) - vec.z * sin(angle),
        .z = vec.y * sin(angle) + vec.z * cos(angle)
    };
    return vec3;
}
//Rotation Function for y-axis
vec3_t vec3_rotate_y(vec3_t vec, float angle)
{
    vec3_t vec3 = {
        .x = vec.x * cos(angle) - vec.z * sin(angle),
        .y = vec.y,
        .z = vec.x * sin(angle) + vec.z * cos(angle),

    };
    return vec3;
}
//Rotation Function for z-axis
vec3_t vec3_rotate_z(vec3_t vec, float angle)
{
    vec3_t vec3 = {
        .x = vec.x * cos(angle) - vec.y * sin(angle),
        .y = vec.x * sin(angle) + vec.y * cos(angle),
        .z = vec.z
    };
    return vec3;
}

//Higher Level helpers
vec3_t transform_point(vec3_t point, vec3_t rotation, vec3_t camera) {
    vec3_t rotated = vec3_rotate_y(point, rotation.y);
    rotated = vec3_rotate_x(rotated, rotation.x);
    rotated = vec3_rotate_z(rotated, rotation.z);
    rotated.z -= camera.z;
    return rotated;
}

