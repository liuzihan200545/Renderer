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
