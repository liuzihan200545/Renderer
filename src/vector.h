#pragma once
#include "math.h"

typedef struct {
    float x;
    float y;
}vec_2t;

typedef struct {
    float x;
    float y;
    float z;
}vec_3t;

//TODO:implement the functions of vectors 2d and 3d
vec_3t rotate_x(vec_3t v,float angle);
vec_3t rotate_y(vec_3t v,float angle);
vec_3t rotate_z(vec_3t v,float angle);

