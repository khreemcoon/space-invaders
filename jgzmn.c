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
 *enemy shooting    [] i've spent about... 5? days working on player shooting. I now realise how much of a fucking PAIN this will be to add. hopefully once i crack the player one this will be super easy lol.
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
typedef struct LL_Bullet{
    Entity* data;
    struct LL_Bullet* next;
}LL_Bullet;
LL_Bullet* head=NULL;
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
    LL_Bullet* tmp;
    for(tmp=head;tmp!=NULL;tmp=tmp->next){
        render_entity(window, tmp->data);
    }
    window_display(window);
}
void shoot(){
    /*fuck around and make me bust ez*/
    Entity* bullet=create_entity(bullet_t, player->x+15, player->y, 2, 8, 0.0, SDL_FLIP_NONE);
    bullet->yvel=-1;
    //i makade da bullte;;; dann füge ich sie zu "linkedlist" hinzu,,,, 
    /*to be completely honest i have no fucking clue what i'm doing*/
    /*making bullet linkedlist item*/LL_Bullet* tmp=malloc(sizeof(LL_Bullet));
                                     tmp->data=bullet;
    /*new entry in the linked list */tmp->next=head;
                                     head=tmp;
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
    //fourth fucking time i swear;
    /*now the fifth.*/
    /*la bullitas!*/
    /*...again.*/
    LL_Bullet* tmp,* prev;
    prev=head;
    for(tmp=head;tmp!=NULL;tmp=tmp->next){
        tmp->data->y+=(tmp->data->yvel*500)*dt;
        if(tmp->data->y<=200){
            /*VVV this isn't the failpoint,,, surpris! VVV*/
            if(tmp==head)
                head=NULL;
            prev->next=tmp->next;
            //will leave this alone free(tmp);
            tmp=prev;
        }
        prev=tmp;
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
