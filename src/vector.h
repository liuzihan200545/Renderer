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

float vec_2_length(vec_2t v);
float vec_3_length(vec_3t v);


vec_2t vec2_add(vec_2t v1,vec_2t v2);
vec_3t vec3_add(vec_3t v1,vec_3t v2);

vec_2t vec2_sub(vec_2t v1,vec_2t v2);
vec_3t vec3_sub(vec_3t v1,vec_3t v2);

float vec2_dot(vec_2t v1,vec_2t v2);
float vec3_dot(vec_3t v1,vec_3t v2);

vec_2t vec2_mul(vec_2t v,float n);
vec_3t vec3_mul(vec_3t v,float n);

vec_2t vec2_div(vec_2t v, float n);
vec_3t vec3_div(vec_3t v, float n);

vec_3t vec3_cross(vec_3t v1,vec_3t v2);

void normalize_vec2(vec_2t *const vector);

void normalize_vec3(vec_3t *const vector);




