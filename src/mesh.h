#pragma once

#include <vector>
#include "vector.h"
#include "triangle.h"
#include <string>

#define N_CUBE_VERTICES 8
#define N_CUBE_FACES (6*2) // 6 cube faces, 2 triangles per face

extern vec_3t cube_vertices[N_CUBE_VERTICES];
extern face_t cube_faces[N_CUBE_FACES];

typedef struct {
    std::vector<vec_3t> vertices;
    std::vector<face_t> faces;
    vec_3t rotation;
}mesh_t;

extern mesh_t mesh;
void Load_the_cube_mesh();
void Load_mesh_from_obj_file(std::string file_name);