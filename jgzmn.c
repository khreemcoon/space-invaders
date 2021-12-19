#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
//gato sexo test 2
int init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) <0)printf("SDL2 has failed to initialize. Error: %s\n", SDL_GetError());
    if(IMG_Init(SDL_INIT_EVERYTHING) < 0)printf("SDL2 Image has failed to initialize. Error: %s\n",IMG_GetError());
    return 1;
}
int main(int argc, char**args){
    int r=init();
    printf("it go\n");
    return 0;
}
