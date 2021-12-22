#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "window.h"
#include "entity.h"
#include "utils.h"
/*Task List:
 *the basic shit    [*]
 *player movement   [*]
 *player shooting   [] hey are you PISSING me how long is this going to take? all of this FUCKING day i've been doing this shit GOY VEY I HATE C I MOVING TO (((RUST)))
 ACHTUNG! MEINE NÜSSE WIRD DEINEN MUND TREFFEN!!!!! AHAHA! DU WIRST SIE PROBIEREN!!!!
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
/*number SEX*/
typedef struct jew_list{
    Entity* data;
    struct jew_list* next;
}jew_list;
jew_list* stage=NULL;
int can_sht=1, r=0;
double dt=0;
int init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) <0)printf("SDL2 has failed to initialize. Error: %s\n", SDL_GetError());
    if(IMG_Init(SDL_INIT_EVERYTHING) < 0)printf("SDL2 Image has failed to initialize. Error: %s\n",IMG_GetError());
    window=create_win(800,600,"game");
    SDL_Texture* player_t=load_texture(window,"src/img/player.png");
    player=create_entity(player_t,30,500,32,64,0.0,SDL_FLIP_NONE);
    shot_t=create_timer(250,0);
    bullet_t=load_texture(window,"src/img/bullet.png");
    stage=malloc(sizeof(jew_list));
    return 1;
}
void die(){
    r=0;
    kill_win(window);
    free(window);window=NULL;
    free(player);player=NULL;
    free(shot_t);shot_t=NULL;
    SDL_Quit();
}
void display(){
    window_clear(window,black);
    render_entity(window,player);
    jew_list* b;
    for(b=stage->next;b!=NULL;b=b->next){
        printf("rendering bullets\n");
        render_entity(window,b->data);
    }
    window_display(window);
}
void shoot(){
    /*fuck around and make me bust ez*/
    Entity* bullet=create_entity(bullet_t, player->x+15, player->y, 2, 8, 0.0, SDL_FLIP_NONE);
    bullet->yvel=-1;
    //i makade da bullte;;; dann füge ich sie zu "linklist" hinzu,,,, 
    jew_list* bullet_l=malloc(sizeof(jew_list));
    bullet_l->data=bullet;
    /*VVVV even with this code order changed it doesn't work VVVV*/
    stage->next=bullet_l;
    stage=bullet_l;
    printf("bullet sex\n");
}
void input(){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type==SDL_QUIT)
            die();
        if(e.type==SDL_KEYDOWN){
            switch(e.key.keysym.sym){
                case SDLK_ESCAPE:
                    die();
                    break;
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
    /*goy list*/
    /*this is my THIRD FUCKING TIME IF IT NOT WORK THEN SEX IS FUCK NAHHAHAHAHAHAH!!H!HAHHAHAXAXAXAXOXXOOXOXOXOXO O ich habe deinen Vater gefickt,,,*/
    jew_list* b,* prev;
    prev=stage;
    for(b=stage->next;b!=NULL;b=b->next){
        printf("bullet updater\n");
        b->data->y+=b->data->yvel*500*dt;
        if(b->data->y<=200){
            if(b==stage)
                stage=prev;
            prev->next=b->next;
            free(b);
            b=prev;
        }
        prev=b;
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
