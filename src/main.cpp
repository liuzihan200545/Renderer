#include <SDL2/SDL.h>
#include "display.h"
#include "vector.h"
#include "mesh.h"
#include <vector>

std::vector<triangle_t> triangle_to_render;

bool is_running = false;
int fov_factor = 640;
vec_3t camera_position = {0,0,-5};

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
    Load_mesh_from_obj_file("../asserts/cube.obj");
    for(auto u:mesh.faces){
        std::cout<<mesh.vertices[u.a-1].y<<" "<<mesh.vertices[u.b-1].y<<" "<<mesh.vertices[u.c-1].y<<std::endl;
    }
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

    triangle_to_render.clear();

    mesh.rotation.x += 0.01;
    mesh.rotation.y += 0.01;
    mesh.rotation.z += 0.01;

    for(auto u:mesh.faces){
        vec_3t face_vertices[3];
        face_vertices[0] = mesh.vertices[u.a - 1];
        face_vertices[1] = mesh.vertices[u.b - 1];
        face_vertices[2] = mesh.vertices[u.c - 1];

        triangle_t projected_triangle;

        // loop all these vertices of the current face and apply transformations
        for(int j = 0;j<3;j++){
            vec_3t transformed_vertex = face_vertices[j];
            transformed_vertex = rotate_x(transformed_vertex,mesh.rotation.x);
            transformed_vertex = rotate_y(transformed_vertex,mesh.rotation.y);
            transformed_vertex = rotate_z(transformed_vertex,mesh.rotation.z);

            transformed_vertex.z -= camera_position.z;

            vec_2t projected_point = projection(transformed_vertex);
            projected_point.x += (window_width/2);
            projected_point.y += (window_height/2);
            projected_triangle.points[j] = projected_point;
        }
        // Save the projected triangle
        triangle_to_render.push_back(projected_triangle);
    }
}

void render(){
    //SDL_SetRenderDrawColor(renderer,255,0,0,255);
    //SDL_RenderClear(renderer);
    //...
    for(auto triangle:triangle_to_render){
        draw_triangle(triangle,white);
    }

    render_color_buffer();
    clear_color_buffer(0x00000000);
    //...
    SDL_RenderPresent(renderer);
}