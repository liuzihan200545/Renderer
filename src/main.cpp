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
    //Initialize render mode and and triangle culling mode
    render_method = RENDER_WIRE;
    cull_method = CULL_BACKFACE;
    color_buffer = (uint32_t*)malloc(sizeof(uint32_t)*window_width*window_height);
    color_buffer_texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            window_width,
            window_height
            );
    Load_mesh_from_obj_file("../asserts/f22.obj");

    vec_3t v1 {1,1,1};
    vec_3t v2 {1,1,1};
    //std::cout<<vec3_mul(v1,v2)<<std::endl;
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
            if(event.key.keysym.sym == SDLK_1){
                render_method = RENDER_WIRE_VERTEX;
            }
            if(event.key.keysym.sym == SDLK_2){
                render_method = RENDER_WIRE;
            }
            if(event.key.keysym.sym == SDLK_3){
                render_method = RENDER_FILL_TRIANGLE;
            }
            if(event.key.keysym.sym == SDLK_4){
                render_method = RENDER_FILL_TRIANGLE_WIRE;
            }
            if(event.key.keysym.sym == SDLK_c){
                cull_method = CULL_BACKFACE;
            }
            if(event.key.keysym.sym == SDLK_d){
                cull_method = CULL_NONE;
            }
            if(event.key.keysym.sym == SDLK_w){
                camera_position.z += 0.5;
            }
            if(event.key.keysym.sym == SDLK_s){
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
        vec_3t transformed_vertices[3];
        // loop all these vertices of the current face and apply transformations
        for(int j = 0;j<3;j++) {
            vec_3t transformed_vertex = face_vertices[j];
            transformed_vertex = rotate_x(transformed_vertex, mesh.rotation.x);
            transformed_vertex = rotate_y(transformed_vertex, mesh.rotation.y);
            transformed_vertex = rotate_z(transformed_vertex, mesh.rotation.z);

            transformed_vertex.z -= camera_position.z;
            transformed_vertices[j] = transformed_vertex;
        }
        if(cull_method == CULL_BACKFACE){
            vec_3t vector_a = transformed_vertices[0];
            vec_3t vector_b = transformed_vertices[1];
            vec_3t vector_c = transformed_vertices[2];

            vec_3t vector_ab = vec3_sub(vector_b,vector_a);
            vec_3t vector_ac = vec3_sub(vector_c,vector_a);

            normalize_vec3(&vector_ab);
            normalize_vec3(&vector_ac);

            vec_3t normal = vec3_cross(vector_ab,vector_ac);
            normalize_vec3(&normal);

            vec_3t camera_ray = vec3_sub(camera_position,vector_a);

            float dot_normal_camera = vec3_dot(normal,camera_ray);

            if(dot_normal_camera<0){
                continue;
            }
        }
        for(int j = 0;j<3;j++){

            vec_2t projected_point = projection(transformed_vertices[j]);
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
        if(render_method == RENDER_FILL_TRIANGLE || render_method == RENDER_FILL_TRIANGLE_WIRE){
            draw_filled_triangle(triangle,grey);
        }

        if(render_method == RENDER_WIRE || render_method == RENDER_WIRE_VERTEX || render_method == RENDER_FILL_TRIANGLE_WIRE){
            draw_triangle(triangle,yellow);
        }

        if(render_method == RENDER_WIRE_VERTEX){
            for(int j = 0;j<3;j++){
                draw_rectangle(triangle.points[j].x-3,triangle.points[j].y-3,6,6,red);
            }
        }


    }


    render_color_buffer();
    clear_color_buffer(0x00000000);
    //...
    SDL_RenderPresent(renderer);
}