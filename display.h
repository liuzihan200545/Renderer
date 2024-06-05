// A library contains the content about the display on the screen.
#pragma once
#include <iostream>
#include <SDL2/SDL.h>

extern uint32_t* color_buffer;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* color_buffer_texture;
extern int window_width;
extern int window_height;

bool initialize_window();

void draw_grid();
void draw_rectangle(int pos_x,int pos_y,int width,int height,uint32_t color);
void render_color_buffer();
void clear_color_buffer(uint32_t color);
void destroy_window();
void draw_pixel(int x,int y,uint32_t color);




