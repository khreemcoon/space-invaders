#include "utils.h"
Timer* create_timer(unsigned int delay, int single){
    Timer* timer=NULL;
    timer=malloc(sizeof(Timer));
    timer->delay=delay;
    timer->last=0;
    timer->single=single;
    return timer;
}
void timer_process(Timer* t){
    t->current=SDL_GetTicks();
    if(t->shot != 5){
        t->shot=0;
        if(t->current>t->last+t->delay){
            if(t->single)
                t->shot=5;
            else
                t->shot=1;
            t->last=t->current;
        }
    }
}
