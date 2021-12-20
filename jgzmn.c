#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "window.h"
#include "entity.h"
#include "utils.h"
/*Task List:
 *the basic shit    [*]
 *player movement   [*]
 *player shooting   []
 *enemy movement    []
 *enemy shooting    []
 *walls             []
 *sfx               []
 *death             []
 *win               []
 *main menu         []
 *fancy shit[]
*/
SDL_Color white={255,255,255}, black={0,0,0};
Window* window=NULL;
Entity* player=NULL;
SDL_Texture* bullet_t=NULL;
Timer* shot_t=NULL;
//LINKED FUCK PISS SHITVVVVVVVVVV
typedef struct Bullet{
    Entity* value;
    struct Bullet* next;
}Bullet;
/*number SEX*/
int can_sht=1;
int r=0;
double dt=0;
int init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) <0)printf("SDL2 has failed to initialize. Error: %s\n", SDL_GetError());
    if(IMG_Init(SDL_INIT_EVERYTHING) < 0)printf("SDL2 Image has failed to initialize. Error: %s\n",IMG_GetError());
    window=create_win(800,600,"game");
    SDL_Texture* player_t=load_texture(window,"src/img/player.png");
    player=create_entity(player_t,30,500,32,64,0.0,SDL_FLIP_NONE);
    shot_t=create_timer(500,0);
    bullet_t=load_texture(window,"src/img/bullet.png");
    return 1;
}
void die(){
    r=0;
    kill_win(window);
    free(window);window=NULL;
    SDL_Quit();
}
void display(){
    window_clear(window,black);
    render_entity(window,player);
    for(int i=0;i<255;++i){
        if(bullets[i]!=NULL)
            render_entity(window,bullets[i]);
    }
    window_display(window);
}
void shoot(){
    /*fuck around and make me bust ez*/
    Entity* bullet=create_entity(bullet_t, player->x+15, player->y, 2, 8, 0.0, SDL_FLIP_NONE);
    //i maka da bvulle,t,,, ^^^
    Bullet* current=malloc(sizeof(Bullet));
    current->value=bullet;
}
void input(){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type==SDL_QUIT)
            die();
        if(e.type==SDL_KEYDOWN){
            switch(e.key.keysym.sym){
                case SDLK_RIGHT:
                    player->xvel=1;
                    break;
                case SDLK_LEFT:
                    player->xvel=-1;
                    break;
                case SDLK_SPACE:
                    if(can_sht){
                        can_sht=0;
                        shoot();
                    }
                    break;
            }
        }
        if(e.type==SDL_KEYUP){
            switch(e.key.keysym.sym){
                case SDLK_RIGHT:
                    if(player->xvel>0)
                        player->xvel=0;
                    break;
                case SDLK_LEFT:
                    if(player->xvel<0)
                        player->xvel=0;
                    break;
            }
        }
    }
}
void update(){
    timer_process(shot_t);
    if(shot_t->shot){
        if(!can_sht)
            can_sht=1;
    }
    player->x+=(player->xvel*250)*dt;
    for(int i=0;i<255;++i){
        if(bullets[i]!=NULL)
            bullets[i]->y += (bullets[i]->yvel*500)*dt;
    }
}
int main(int argc, char**args){
    r=init();
    Uint64 now=SDL_GetTicks(),last=0;
    const int FPS=60,DELAY=1000/FPS;
    Uint32 fs;
    int ft;
    while(r){
        now=SDL_GetTicks();
        dt=(double)(now-last)*0.001;
        last=now;
        fs=SDL_GetTicks();
        display();
        input();
        update();
        ft=fs-SDL_GetTicks();
        if(DELAY>ft)
            SDL_Delay(DELAY-ft);
    }
    return 0;
}
