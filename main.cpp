#include <iostream>
#include <SDL2/SDL.h>
#include "display.h"
#include "vector.h"

const int N_Points = 9 * 9 * 9;
bool is_running = false;
int fov_factor = 128;
vec_3t cube_points[N_Points];
vec_2t projected_cube_points[N_Points];


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

    int point_count = 0;

    for(float x = -1;x<=1;x+=0.25){
        for(float y = -1;y<=1;y+=0.25){
            for(float z = -1;z<=1;z+=0.25){
                cube_points[point_count++] = {x,y,z};
            }
        }
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
            break;
    }
}

vec_2t projection(vec_3t point){
    vec_2t new_vec = {
            fov_factor * point.x,
            fov_factor*point.y
    };
    return new_vec;
}

void update(){
    for(int i = 0;i<N_Points;i++){
        projected_cube_points[i] = projection(cube_points[i]);
    }

}

void render(){
    //SDL_SetRenderDrawColor(renderer,255,0,0,255);
    //SDL_RenderClear(renderer);
    //...

    //draw_gird();
    for(int i = 0;i<N_Points;i++){
        vec_2t projected_point = projected_cube_points[i];
        int target_x = projected_point.x + window_width/2;
        int target_y = projected_point.y + window_height/2;
        draw_rectangle(target_x,
                       target_y,
                       4,
                       4,
                       0xFF00FF00);
    }

    render_color_buffer();

    clear_color_buffer(0x00000000);

    vec_3t vector3d = {1.0,2.0,3.0};

    //...
    SDL_RenderPresent(renderer);
}