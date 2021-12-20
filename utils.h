#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <SDL2/SDL.h>
typedef struct{
    unsigned int delay, last, current;
    int shot, single;
}Timer;
Timer* create_timer(unsigned int delay, int single);
void timer_process(Timer* t);
#endif