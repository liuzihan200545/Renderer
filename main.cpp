#include <iostream>
#include <SDL2/SDL.h>

uint32_t* color_buffer;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* color_buffer_texture = nullptr;
bool is_running = false;
int window_width = 800;
int window_height = 600;

bool initialize_window(){
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
        fprintf(stderr,"Error Initialize SDL!\n");
        return false;
    }
    //TODO:Create a window.
    window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            800,
            600,
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

void setup();
void process_input();
void update();
void render();
void destroy_window();
void render_color_buffer();

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
            break;
    }
}

void clear_color_buffer(uint32_t color){
    for(int y = 0;y<window_height;y++){
        for(int x = 0;x<window_width;x++){
            color_buffer[y*window_width+x] = color;
        }
    }
}

void update(){

}

void destroy_window(){
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void render_color_buffer(){
    SDL_UpdateTexture(
            color_buffer_texture,
            nullptr,
            color_buffer,
            (int)sizeof(uint32_t)*window_width
            );
    SDL_RenderCopy(renderer,color_buffer_texture, nullptr, nullptr);
}

void render(){
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderClear(renderer);
    //...
    render_color_buffer();
    clear_color_buffer(0xFFFFFF00);



    //...
    SDL_RenderPresent(renderer);
}