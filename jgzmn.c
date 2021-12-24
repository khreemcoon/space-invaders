#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "window.h"
#include "entity.h"
#include "utils.h"
/*Task List:
 *the basic shit    [*]
 *player movement   [*]
 *player shooting   [*] 
 *enemy movement    [*]
 *enemy shooting    [*] 
 *walls             []
 *sfx               []
 *death             [/]
 *win               []
 *main menu         []
 *fancy shit        []
*/
SDL_Color white={255,255,255}, black={0,0,0};
Window* window=NULL;
Entity* player=NULL;
SDL_Texture* bullet_t=NULL;
Timer* shot_t=NULL;
Timer* shot_et=NULL;
typedef struct LL_Bullet{
    Entity* data;
    struct LL_Bullet* next;
}LL_Bullet;
typedef struct LL_Enemy{
    Entity* data;
    struct LL_Enemy* next;
}Enemy;
Enemy* head_e=NULL;
LL_Bullet* head_b=NULL;
int can_sht=1, r=0;
double dt=0;
int init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) <0)printf("SDL2 has failed to initialize. Error: %s\n", SDL_GetError());
    if(IMG_Init(SDL_INIT_EVERYTHING) < 0)printf("SDL2 Image has failed to initialize. Error: %s\n",IMG_GetError());
    srand(time(NULL));
    window=create_win(800,600,"game");
    SDL_Texture* player_t=load_texture(window,"src/img/player.png");
    player=create_entity(player_t,30,500,32,64,0.0,SDL_FLIP_NONE, 3);
    shot_t=create_timer(250,0);
    bullet_t=load_texture(window,"src/img/bullet.png");
    SDL_Texture* enemy_t=load_texture(window,"src/img/enemy.png");
    for(int i=0;i<5;++i){
        Entity* tmp_data=create_entity(enemy_t,100*i,30,32,32,0.0,SDL_FLIP_NONE, 3);
        tmp_data->xvel=1;
        Enemy* tmp_ll=malloc(sizeof(Enemy));
        tmp_ll->data=tmp_data;
        tmp_ll->next=head_e;
        head_e=tmp_ll;
    }
    shot_et=create_timer(1500,0);
    return 1;
}
void die(){
    r=0;
    kill_win(window);
    free(window);window=NULL;
    free(player);player=NULL;
    free(shot_t);shot_t=NULL;
    free(head_b);head_b=NULL;
    SDL_Quit();
}
int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2){
    return(x1<x2+w2 &&
           y1<y2+h2 &&
           x2<x1+w1 &&
           y2<y1+h1);
}
void display(){
    window_clear(window,black);
    render_entity(window,player);
    LL_Bullet* tmp;
    for(tmp=head_b;tmp!=NULL;tmp=tmp->next){
        if(tmp->data->hp > 0)
            render_entity(window, tmp->data);
    }
    Enemy* tmp_e;
    for(tmp_e=head_e;tmp_e!=NULL;tmp_e=tmp_e->next){
        render_entity(window, tmp_e->data);
    }
    window_display(window);
}
void shoot(float p_x, float p_y, int yvel){
    Entity* bullet=create_entity(bullet_t, p_x, p_y, 2, 8, 0.0, SDL_FLIP_NONE, 1);
    bullet->yvel=yvel;
    LL_Bullet* tmp=malloc(sizeof(LL_Bullet));
    tmp->data=bullet;
    tmp->next=head_b;
    head_b=tmp;
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
                        shoot(player->x+15, player->y,-1);
                    }
                    break;
            }
            /*WHORE PIG!*/
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
void enemy_update(){
    Enemy* tmp,* prev;
    prev=head_e;
    timer_process(shot_et);
    for(tmp=head_e;tmp!=NULL;tmp=tmp->next){
        if(tmp->data->hp > 0){
            tmp->data->x+=tmp->data->xvel*100*dt;
            if(tmp->data->x >= 780 || tmp->data->x <=0)
                tmp->data->xvel = -tmp->data->xvel;
            if(shot_et->shot){
                int shoot_c=rand()%10;
                if(shoot_c==1)
                    shoot(tmp->data->x+15,tmp->data->y+32,1);
            }
        }
        if(tmp->data->hp<=0){
            if(tmp==head_e)
                head_e==NULL;
            prev->next=tmp->next;
            tmp=prev;
        }
        prev=tmp;
    }
}
void bullet_update(){
    LL_Bullet* tmp,* prev;
    prev=head_b;
    for(tmp=head_b;tmp!=NULL;tmp=tmp->next){
        tmp->data->y+=(tmp->data->yvel*500)*dt;
        if(tmp->data->y<=-20 || tmp->data->y>=820 || tmp->data->hp <=0){
            if(tmp==head_b)
                head_b=NULL;
            prev->next=tmp->next;
            tmp=prev;
        }
        prev=tmp;
        Enemy* enemy,* prev_enemy;
        prev_enemy=head_e;
        for(enemy=head_e;enemy!=NULL;enemy=enemy->next){
            if(collision(enemy->data->x,enemy->data->y,32,32,tmp->data->x,tmp->data->y,2,8)){
                --enemy->data->hp;
                --tmp->data->hp;
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
    bullet_update();
    enemy_update();
    player->x+=(player->xvel*250)*dt;
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
