#ifndef WINDOW_H
#define WINDOW_H
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
typedef struct{
    SDL_Window* win;
    SDL_Renderer* rend;
} Window;
Window* create_win(int w, int h, char* win_name);
void window_clear(Window* w, SDL_Color color);
void window_display(Window* w);
void kill_win(Window* w);
SDL_Texture* load_texture(Window* w, char* path);
void render_texture(Window* w, SDL_Texture* tex, float x, float y, int wi, int h, double angle, SDL_RendererFlip flip);
#endif
