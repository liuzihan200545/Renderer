#include "mesh.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>

vec_3t cube_vertices[N_CUBE_VERTICES] = {
        {.x = -1,.y = -1,.z = -1}, //1
        {.x = -1,.y =  1,.z = -1}, //2
        {.x =  1,.y =  1,.z = -1}, //3
        {.x =  1,.y = -1,.z = -1}, //4
        {.x =  1,.y =  1,.z =  1}, //5
        {.x =  1,.y = -1,.z =  1}, //6
        {.x = -1,.y =  1,.z =  1}, //7
        {.x = -1,.y = -1,.z =  1}  //8
};

face_t cube_faces[N_CUBE_FACES] = {
        // front
        {.a = 1,.b = 2,.c = 3},
        {.a = 1,.b = 3,.c = 4},
        // right
        {.a = 4,.b = 3,.c = 5},
        {.a = 4,.b = 5,.c = 6},
        // back
        {.a = 6,.b = 5,.c = 7},
        {.a = 6,.b = 7,.c = 8},
        // left
        {.a = 8,.b = 7,.c = 2},
        {.a = 8,.b = 2,.c = 1},
        // top
        {.a = 2,.b = 7,.c = 5},
        {.a = 2,.b = 5,.c = 3},
        // bottom
        {.a = 6,.b = 8,.c = 1},
        {.a = 6,.b = 1,.c = 4}
};

mesh_t mesh = {
        std::vector<vec_3t>{},
        std::vector<face_t>{},
        vec_3t {0.f,0.f,0.f}
};

void Load_the_cube_mesh(){
    for(auto u:cube_vertices){
        mesh.vertices.push_back(u);
    }
    for(auto u:cube_faces){
        mesh.faces.push_back(u);
    }
    mesh.rotation = {0.f,0.f,0.f};
}

void Load_mesh_from_obj_file(std::string file_name) {
    //TODO:create the definition of a
    // function that load the data from a obj file
    // and turn it into the mesh file.
    std::ifstream fin;
    fin.open(file_name);
    std::string data;
    while(getline(fin,data)){
        //std::cout<<data<<std::endl;
        if(strcmp(data.substr(0,2).c_str(),"v ")==0){
            vec_3t vertex;
            sscanf(data.c_str(),"v %f %f %f",&vertex.x,&vertex.y,&vertex.z);
            mesh.vertices.push_back(vertex);
        }
        if(strcmp(data.substr(0,2).c_str(),"f ")==0){
            int vertex_indices[3];
            int texture_indices[3];
            int normal_indices[3];
            sscanf(data.c_str(),"f %d/%d/%d %d/%d/%d %d/%d/%d",&vertex_indices[0],&texture_indices[0],&normal_indices[0],
                   &vertex_indices[1],&texture_indices[1],&normal_indices[1],
                   &vertex_indices[2],&texture_indices[2],&normal_indices[2]);
            face_t face {
                .a = vertex_indices[0],
                .b = vertex_indices[1],
                .c = vertex_indices[2]
            };
            mesh.faces.push_back(face);
        }
    }
    fin.close();

}
