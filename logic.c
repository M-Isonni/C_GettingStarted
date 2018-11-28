#include<SDL.h>
//INPUTS
//init the array of keys at false
void KeysInit(SDL_bool keys[]) {
    for (int i=0;i<322;i++){
        keys[i]=SDL_FALSE;
    }
}


//hadling inputs, being called inside the while will check if inside the array of key, at the position of the key we choose, is set at true(has been pressed), and ill act accordingly
//keys[] is already a pointer so no need to pass it as a pointer, rect and running need to be passed to function as pointers cause we need to work on them, speed can be passed as a copy.
void handleinput(SDL_bool KEYS[],SDL_Rect *rect, int *running, int speed ) {
         if(KEYS[SDL_SCANCODE_A]) { 
            *running=0;
        }
        if(KEYS[SDL_SCANCODE_LEFT]){
            rect->x-=speed;
        }
         if(KEYS[SDL_SCANCODE_RIGHT]){
            rect->x+=speed;
        }
         if(KEYS[SDL_SCANCODE_UP]){
            rect->y-=speed;
        }
         if(KEYS[SDL_SCANCODE_DOWN]){
            rect->y+=speed;
        }   
   
}

void manage_inputs (SDL_Event *event, SDL_Rect *rect,int speed) {
    if(event->type==SDL_KEYDOWN){

        switch(event->key.keysym.scancode){
            case SDL_SCANCODE_LEFT:
             rect->x-=speed;
             break;
             case SDL_SCANCODE_RIGHT:
             rect->x+=speed;
             break;
             case SDL_SCANCODE_UP:
             rect->y-=speed;
             break;
             case SDL_SCANCODE_DOWN:
             rect->y+=speed;
             break;
             default:
             break;
        }
    }

}