#include "display.h"
#include <SDL2/SDL.h>
#include "vector.h"
#include "triangle.h"

#define x0 triangle.points[0].x
#define y0 triangle.points[0].y
#define x1 triangle.points[1].x
#define y1 triangle.points[1].y
#define x2 triangle.points[2].x
#define y2 triangle.points[2].y

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


void draw_line(float x_0, float y_0,float x_1, float y_1, uint32_t color) {
    float delta_x = (x_1 - x_0);
    float delta_y = (y_1 - y_0);
    float side_length = abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);
    float x_inc = delta_x / side_length;
    float y_inc = delta_y / side_length;

    float current_x = x_0;
    float current_y = y_0;

    for(int i = 0;i<=side_length;i++){
        draw_pixel(round(current_x), round(current_y),color);
        current_x += x_inc;
        current_y += y_inc;
    }
}


void swap(vec_2t &p1, vec_2t &p2) {
    vec_2t temp = p2;
    p2 = p1;
    p1 = temp;
}

void draw_plat_top(int x_0,int y_0,int x_1,int y_1,int x_2,int y_2,uint32_t color){
    float inv_slope_1 = (float) (x_2 - x_0) / (y_2-y_0);
    float inv_slope_2 = (float) (x_2 - x_1) / (y_2-y_1);
    float x_start = x_2;
    float x_end = x_2;

    for(int y = y_2;y>=y_0;y--){
        draw_line(x_start, y, x_end, y, color);
        x_start -= inv_slope_1;
        x_end -= inv_slope_2;
    }
}

void draw_plat_bottom(int x_0,int y_0,int x_1,int y_1,int x_2,int y_2,uint32_t color){
    float inv_slope_1 = (float) (x_1 - x_0) / (y_1-y_0);
    float inv_slope_2 = (float) (x_2 - x_0) / (y_2-y_0);
    float x_start = x_0;
    float x_end = x_0;

    for(int y = y_0;y<=y_2;y++){
        draw_line(x_start, y, x_end, y, color);
        x_start += inv_slope_1;
        x_end += inv_slope_2;
    }
}

void draw_filled_triangle(triangle_t triangle, uint32_t color) {
    if(triangle.points[0].y>triangle.points[1].y){
        swap(triangle.points[0],triangle.points[1]);
    }
    if(triangle.points[0].y>triangle.points[2].y){
        swap(triangle.points[0],triangle.points[2]);
    }
    if(triangle.points[1].y>triangle.points[2].y){
        swap(triangle.points[1],triangle.points[2]);
    }

    float My = y1;
    float Mx = (x2-x0)*(y1-y0)/(y2-y0) + x0;

    if(y0 == y1){
        draw_plat_top(x1,y1,Mx,My,x2,y2,color);
    }
    else if(y1 == y2){
        draw_plat_bottom(x0,y0,x1,y1,Mx,My,color);
    }
    else{
        draw_plat_bottom(x0,y0,x1,y1,Mx,My,color);
        draw_plat_top(x1,y1,Mx,My,x2,y2,color);
    }
}