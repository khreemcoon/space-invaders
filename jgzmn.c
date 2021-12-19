#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "window.h"
/*Task List:
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
int r=0;
int init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) <0)printf("SDL2 has failed to initialize. Error: %s\n", SDL_GetError());
    if(IMG_Init(SDL_INIT_EVERYTHING) < 0)printf("SDL2 Image has failed to initialize. Error: %s\n",IMG_GetError());
    window=create_win(800,600,"game");
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
