#ifndef VECTOR_H
#define VECTOR_H


#include <math.h>



typedef struct 
{
    float x;
    float y;
}vec2_t;

typedef struct 
{
    float x;
    float y;
    float z;
}vec3_t;

#include "globals.h"


// TODO: add functions to manipulate vectors 2D and 3D

//Orthographic Projection
vec2_t Orthograpgic_project(vec3_t vec3);
//Perspective Projection
vec2_t Perspective_project(vec3_t vec3);
//Rotation Function for x-axis
vec3_t vec3_rotate_x(vec3_t vec, float angle);
//Rotation Function for y-axis
vec3_t vec3_rotate_y(vec3_t vec, float angle);
//Rotation Function for z-axis
vec3_t vec3_rotate_z(vec3_t vec, float angle);

//Higher Level helpers
vec3_t transform_point(vec3_t point, vec3_t rotation, vec3_t camera);

#endif // VECTOR_H