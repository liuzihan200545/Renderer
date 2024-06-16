// A library contains the content about the display on the screen.
#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include "vector.h"
#include "triangle.h"

#define FPS 120
#define FRAME_TARGET_TIME (1000 / FPS)

extern uint32_t* color_buffer;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* color_buffer_texture;
extern int window_width;
extern int window_height;

enum Color{
    white = 0xFFFFFFFF,
    yellow = 0xFFFFFF00,
    red = 0xFFFF0000,
    black = 0xFF000000
};

bool initialize_window();

void draw_grid();
void draw_rectangle(int pos_x,int pos_y,int width,int height,uint32_t color);
void draw_line(vec_2t p0,vec_2t p1,uint32_t color);
void draw_triangle(triangle_t triangle,uint32_t color);
void draw_triangle_plane(triangle_t triangle,uint32_t color);
void render_color_buffer();
void clear_color_buffer(uint32_t color);
void destroy_window();
void draw_pixel(int x,int y,uint32_t color);
void draw_line(float x0, float y0,float x1, float y1, uint32_t color);



