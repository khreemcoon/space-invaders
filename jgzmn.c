#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "window.h"
#include "entity.h"
/*Task List:
 *the basic shit(rendering etc etc)[*]
 *player movement []
 *player shooting []
 *enemy movement []
 *enemy shooting []
 *walls []
 *sfx []
 *death []
 *win []
 *main menu []
*/
SDL_Color white={255,255,255};
Window* window=NULL;
Entity* player=NULL;
int r=0;
int init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) <0)printf("SDL2 has failed to initialize. Error: %s\n", SDL_GetError());
    if(IMG_Init(SDL_INIT_EVERYTHING) < 0)printf("SDL2 Image has failed to initialize. Error: %s\n",IMG_GetError());
    window=create_win(800,600,"game");
    SDL_Texture* player_t=load_texture(window,"src/img/player.png");
    player=create_entity(player_t,30,70,16,32,0.0,SDL_FLIP_NONE);
    return 1;
}
void die(){
    r=0;
    kill_win(window);
    free(window);window=NULL;
    SDL_Quit();
}
void display(){
    window_clear(window, white);
    render_entity(window,player);
    window_display(window);
}
void input(){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type==SDL_QUIT)
            die();
    }
}
int main(int argc, char**args){
    r=init();
    while(r){
        display();
        input();
    }
    return 0;
}
