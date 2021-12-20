#ifndef ENTITY_H
#define ENTITY_H
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
typedef struct{
    SDL_Texture* tex;
    float x, y;
    int w, h, xvel, yvel;
    double angle;
    SDL_RendererFlip flip;
}Entity;
Entity* create_entity(SDL_Texture* tex, float x, float y, int w, int h, double angle, SDL_RendererFlip flip);
#endif
