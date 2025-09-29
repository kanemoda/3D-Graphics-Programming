#ifndef VECTOR_H
#define VECTOR_H



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

#define FOV_FACTOR 120.0f

// TODO: add functions to manipulate vectors 2D and 3D

//Orthographic Projection
vec2_t project(vec3_t vec3);

#endif // VECTOR_H