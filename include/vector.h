#ifndef VECTOR_H
#define VECTOR_H

#include "globals.h"



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


// TODO: add functions to manipulate vectors 2D and 3D

//Orthographic Projection
vec2_t Orthograpgic_project(vec3_t vec3);
//Perspective Projection
vec2_t Perspective_project(vec3_t vec3);

#endif // VECTOR_H