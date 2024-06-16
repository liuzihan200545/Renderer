#include "display.h"
#include <SDL2/SDL.h>
#include "vector.h"
#include "triangle.h"

uint32_t* color_buffer = nullptr;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* color_buffer_texture = nullptr;
int window_width = 800;
int window_height = 600;


// Initialize the Main Window of the program,and also create the renderer of the window.
bool initialize_window(){
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
        fprintf(stderr,"Error Initialize SDL!\n");
        return false;
    }
    //Use the SDL to query what is the full screen max.
    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0,&display_mode);
    window_width = display_mode.w;
    window_height = display_mode.h;
    //TODO:Create a window.
    window = SDL_CreateWindow(
            nullptr,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            window_width,
            window_height,
            SDL_WINDOW_BORDERLESS
    );
    if(!window){
        fprintf(stderr,"Error Create a Window!\n");
        return false;
    }
    //TODO:Create a renderer.
    renderer = SDL_CreateRenderer(window,-1,0);
    if(!renderer){
        fprintf(stderr,"Error Create a Renderer!\n");
        return false;
    }
    return true;
}

// Draw a gird on the window.
void draw_grid() {
    for(int y = 0;y<window_height;y++){
        for(int x = 0;x<window_width;x++){
            if(x%40==0||y%40==0){
                color_buffer[y*window_width+x] = 0xFF333333;
            }
        }
    }
}

// Draw a rectangle on the screen.
void draw_rectangle(int pos_x,int pos_y,int width,int height,uint32_t color){
    for(int y = pos_y;y<pos_y+height;y++){
        for(int x = pos_x;x<pos_x+width;x++){
            //color_buffer[y*window_width+x] = color;
            draw_pixel(x,y,color);
        }
    }
}

// Fully fill the whole color_buffer with the selected color.
void clear_color_buffer(uint32_t color){
    for(int y = 0;y<window_height;y++){
        for(int x = 0;x<window_width;x++){
            color_buffer[y*window_width+x] = color;
        }
    }
}

// Transform the color_buffer to the color_buffer_texture.
void render_color_buffer(){
    SDL_UpdateTexture(
            color_buffer_texture,
            nullptr,
            color_buffer,
            (int)sizeof(uint32_t)*window_width
    );
    SDL_RenderCopy(renderer,color_buffer_texture, nullptr, nullptr);
}

// free the color_buffer,delete the SDL_renderer,SDL_window,SDL_everything.
void destroy_window(){
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void draw_pixel(int x, int y, uint32_t color) {
    if(x>=0 && x<window_width && y>=0 && y<window_height){
        color_buffer[y*window_width+x] = color;
    }
}

// DDA Line Drawing Algorithm
void draw_line(vec_2t p0,vec_2t p1, uint32_t color) {
    float delta_x = (p1.x - p0.x);
    float delta_y = (p1.y - p0.y);
    float side_length = abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);
    float x_inc = delta_x / side_length;
    float y_inc = delta_y / side_length;

    float current_x = p0.x;
    float current_y = p0.y;

    for(int i = 0;i<=side_length;i++){
        draw_pixel(round(current_x), round(current_y),color);
        current_x += x_inc;
        current_y += y_inc;
    }
}

// Draw the outline of the triangle use the selected color.
void draw_triangle(triangle_t triangle, uint32_t color) {
    draw_line(triangle.points[0],triangle.points[1],color);
    draw_line(triangle.points[1],triangle.points[2],color);
    draw_line(triangle.points[2],triangle.points[0],color);
}

void draw_line(float x0, float y0,float x1, float y1, uint32_t color) {
    float delta_x = (x1 - x0);
    float delta_y = (y1 - y0);
    float side_length = abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);
    float x_inc = delta_x / side_length;
    float y_inc = delta_y / side_length;

    float current_x = x0;
    float current_y = y0;

    for(int i = 0;i<=side_length;i++){
        draw_pixel(round(current_x), round(current_y),color);
        current_x += x_inc;
        current_y += y_inc;
    }
}