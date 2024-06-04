#include <iostream>
#include <SDL2/SDL.h>

SDL_Window* window;
SDL_Renderer* renderer;

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
    //TODO:Create a renderer.
    if(!window){
        fprintf(stderr,"Error Create a Window!\n");
        return false;
    }
    renderer = SDL_CreateRenderer(window,-1,0);
    if(!renderer){
        fprintf(stderr,"Error Create a Renderer!\n");
        return false;
    }
    return true;
}


int main(){
    bool is_running = initialize_window();
    std::cout<<is_running<<std::endl;
    return 0;
}