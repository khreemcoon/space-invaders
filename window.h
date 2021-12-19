#ifndef WINDOW_H
#define WINDOW_H
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
typedef struct{
    SDL_Window* win;
    SDL_Renderer* rend;
} Window;
Window* create_win(int w, int h, char* win_name){
    Window* win;
    win=malloc(sizeof(Window));
    win->win=SDL_CreateWindow(win_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    win->rend=SDL_Create_renderer(win->win, -1, SDL_RENDERER_ACCELERATED);
    return win;
}
void clear(Window* w, SDL_Color color){
    SDL_SetRenderDrawColor(w->rend, color.r,color.g,color.b,255);
    SDL_RenderClear(w->rend);
}
void dipslay(Window* w)
#endif
