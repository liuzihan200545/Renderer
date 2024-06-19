#include "vector.h"

vec_3t rotate_x(vec_3t v, float angle) {
    vec_3t rotated_vector = {
            .x = v.x,
            .y = v.y * cos(angle) - v.z * sin(angle),
            .z = v.y * sin(angle) + v.z * cos(angle)
    };
    return rotated_vector;
}

vec_3t rotate_y(vec_3t v, float angle) {
    vec_3t rotated_vector = {
            .x = v.x * cos(angle) - v.z * sin(angle),
            .y = v.y,
            .z = v.x * sin(angle) + v.z * cos(angle)
    };
    return rotated_vector;
}

vec_3t rotate_z(vec_3t v, float angle) {
    vec_3t rotated_vector = {
            .x = v.x * cos(angle) - v.y * sin(angle),
            .y = v.x * sin(angle) + v.y * cos(angle)
    };
    return rotated_vector;
}

float vec_3_length(vec_3t v) {
    return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}

float vec_2_length(vec_2t v) {
    return sqrt(v.x*v.x+v.y*v.y);
}

vec_3t vec3_add(vec_3t v1, vec_3t v2) {
    return vec_3t{
        v1.x + v2.x,
        v1.y + v2.y,
        v1.z + v2.z
    };
}

vec_2t vec2_add(vec_2t v1, vec_2t v2) {
    return vec_2t{
            v1.x + v2.x,
            v1.y + v2.y
    };
}

float vec3_dot(vec_3t v1, vec_3t v2) {
    return v1.x*v2.x + v1.y*v2.y+v1.z*v2.z;
}

float vec2_dot(vec_2t v1, vec_2t v2) {
    return v1.x*v2.x + v1.y*v2.y;
}

vec_2t vec2_sub(vec_2t v1, vec_2t v2) {
    return vec_2t{
            v1.x - v2.x,
            v1.y - v2.y
    };
}

vec_3t vec3_sub(vec_3t v1, vec_3t v2) {
    return vec_3t{
            v1.x - v2.x,
            v1.y - v2.y,
            v1.z - v2.z
    };
}

vec_2t vec2_mul(vec_2t v, float n) {
    return vec_2t{
        v.x*n,
        v.y*n
    };
}

vec_3t vec3_mul(vec_3t v, float n) {
    return vec_3t{
        v.x*n,
        v.y*n,
        v.z*n
    };
}

vec_2t vec2_div(vec_2t v, float n) {
    return vec_2t{
            v.x/n,
            v.y/n
    };
}

vec_3t vec3_div(vec_3t v, float n) {
    return vec_3t{
            v.x/n,
            v.y/n,
            v.z/n
    };
}

vec_3t vec3_cross(vec_3t v1, vec_3t v2) {
    return vec_3t {
        v1.y*v2.z - v2.y*v1.z,
        v2.z*v1.z - v1.x*v2.z,
        v1.x*v2.y - v2.x*v1.y
    };
}

void normalize_vec3(vec_3t *const vector) {
    *vector = vec3_div(*vector, vec_3_length(*vector));
}

void normalize_vec2(vec_2t *const vector) {
    *vector = vec2_div(*vector, vec_2_length(*vector));
}


