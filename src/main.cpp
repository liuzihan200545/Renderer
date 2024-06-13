#include <iostream>
#include <SDL2/SDL.h>
#include "display.h"
#include "vector.h"
#include "mesh.h"


triangle_t triangle_to_render[N_MESH_FACES];
bool is_running = false;
int fov_factor = 640;
vec_3t camera_position = {0,0,-5};
vec_3t vector_rotation = {0,0,0};
vec_3t cube_rotation = {0,0,0};

uint32_t previous_frame_time;

void setup();
void process_input();
void update();
void render();
vec_2t projection(vec_3t point);

int main(){
    is_running = initialize_window();
    setup();
    while(is_running){
        process_input();
        update();
        render();
    }
    destroy_window();
    return 0;
}

void setup(){
    color_buffer = (uint32_t*)malloc(sizeof(uint32_t)*window_width*window_height);
    color_buffer_texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            window_width,
            window_height
            );
}

void process_input(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        //TODO: examine the push of the exit button || examine the push of the "Esc" key
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE){
                is_running = false;
            }
            else if(event.key.keysym.sym == SDLK_w){
                camera_position.z += 0.5;
            }
            else if(event.key.keysym.sym == SDLK_s){
                camera_position.z -= 0.5;
            }
            break;
    }
}

vec_2t projection(vec_3t point){
    vec_2t new_vec = {
            fov_factor * point.x / point.z,
            fov_factor*point.y / point.z
    };
    return new_vec;
}

void update(){
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);
    if(time_to_wait >= 0 && time_to_wait < FRAME_TARGET_TIME){
        SDL_Delay(time_to_wait);
        previous_frame_time = SDL_GetTicks();
    }
    cube_rotation.x += 0.01;
    cube_rotation.y += 0.01;
    cube_rotation.z += 0.01;

    for(int i = 0; i < N_MESH_FACES; i++){
        face_t mesh_face = mesh_faces[i];
        vec_3t face_vertices[3];
        face_vertices[0] = mesh_vertices[mesh_face.a - 1];
        face_vertices[1] = mesh_vertices[mesh_face.b - 1];
        face_vertices[2] = mesh_vertices[mesh_face.c - 1];

        triangle_t projected_triangle;

        // loop all these vertices of the current face and apply transformations
        for(int j = 0;j<3;j++){
            vec_3t transformed_vertex = face_vertices[j];
            transformed_vertex = rotate_x(transformed_vertex,cube_rotation.x);
            transformed_vertex = rotate_y(transformed_vertex,cube_rotation.y);
            transformed_vertex = rotate_z(transformed_vertex,cube_rotation.z);

            transformed_vertex.z -= camera_position.z;

            vec_2t projected_point = projection(transformed_vertex);
            projected_point.x += (window_width/2);
            projected_point.y += (window_height/2);
            projected_triangle.points[j] = projected_point;
        }
        // Save the projected triangle
        triangle_to_render[i] = projected_triangle;
    }

}

void render(){
    //SDL_SetRenderDrawColor(renderer,255,0,0,255);
    //SDL_RenderClear(renderer);
    //...
    for(int i = 0;i<N_MESH_FACES;i++){
        triangle_t triangle = triangle_to_render[i];
        draw_rectangle(triangle.points[0].x,triangle.points[0].y,3,3,white);
        draw_rectangle(triangle.points[1].x,triangle.points[1].y,3,3,white);
        draw_rectangle(triangle.points[2].x,triangle.points[2].y,3,3,white);
        draw_line(triangle.points[0].x,triangle.points[0].y,triangle.points[1].x,triangle.points[1].y,white);
        draw_line(triangle.points[1].x,triangle.points[1].y,triangle.points[2].x,triangle.points[2].y,white);
        draw_line(triangle.points[2].x,triangle.points[2].y,triangle.points[0].x,triangle.points[0].y,white);
    }

    render_color_buffer();

    clear_color_buffer(0x00000000);

    //...
    SDL_RenderPresent(renderer);
}