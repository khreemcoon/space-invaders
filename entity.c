#include "entity.h"
Entity* create_entity(SDL_Texture* tex, float x, float y, int w, int h, double angle, SDL_RendererFlip flip){
    Entity* ent;ent= malloc(sizeof(Entity));
    ent->x=x;
    ent->y=y;
    ent->w=w;
    ent->h=h;
    ent->angle=angle;
    ent->flip=flip;
    ent->tex=tex;
    return ent;
}
