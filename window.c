#include "window.h"
Window* create_win(int w, int h, char* win_name){
    Window* win;
    win=malloc(sizeof(Window));
    win->win=SDL_CreateWindow(win_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    win->rend=SDL_CreateRenderer(win->win, -1, SDL_RENDERER_ACCELERATED);
    return win;
}
void window_clear(Window* w, SDL_Color color){
    SDL_SetRenderDrawColor(w->rend, color.r,color.g,color.b,255);
    SDL_RenderClear(w->rend);
}
void window_display(Window* w){
    SDL_RenderPresent(w->rend);
}
void kill_win(Window* w){
    SDL_DestroyWindow(w->win);
}
SDL_Texture* load_texture(Window* w, char* path){
    SDL_Texture* tex=IMG_LoadTexture(w->rend, path);
    if(tex==NULL)
        printf("Failed to load texture! IMG_GetError: %s\n", IMG_GetError());
    return tex;
}
void render_texture(Window* w, SDL_Texture* tex, float x, float y, int wi, int h, double angle, SDL_RendererFlip flip){
    SDL_Rect r={x,y,wi,h};
    SDL_RenderCopyEx(w->rend, tex, NULL, &r, angle, NULL, flip);
}
void render_entity(Window* w, Entity* ent){
    SDL_Rect r={ent->x,ent->y,ent->w,ent->h};
    SDL_RenderCopyEx(w->rend,ent->tex,NULL,&r,ent->angle,NULL,ent->flip);
}
