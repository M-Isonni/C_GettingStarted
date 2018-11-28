#define SDL_MAIN_HANDLED
#include <SDL.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <inputs.h>

int main(int argc, char **argv){

SDL_bool KEYS[322];  //boolean array for keyboard's keys(they are in total 322) USED FOR THE UNITY SIMILAR MANAGING INPUT
int running =1;  
SDL_Rect rect;
int speed=10;

    KeysInit(KEYS);

    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)!=0){
        SDL_Log("error: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Window *Window = SDL_CreateWindow("window",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,SDL_WINDOW_RESIZABLE);  

    if(!Window)
    {
        SDL_Log("error: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Renderer *Renderer=SDL_CreateRenderer(Window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

    if(!Renderer){
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    int x,y,n;
    unsigned char *imagedata=stbi_load("Image.png",&x,&y,&n,0);

    SDL_Texture *texture = SDL_CreateTexture(Renderer,SDL_PIXELFORMAT_BGRA32,SDL_TEXTUREACCESS_STREAMING,x,y);
    if(!texture){
        SDL_Log("Error failed texture %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    unsigned char *pixels =NULL;
    int pitch=0;
    if(SDL_LockTexture(texture,NULL,(void **)&pixels,&pitch)){
        SDL_Log("error failed locking %s", SDL_GetError());
        SDL_Quit();
        return-1;
    }       
   
    SDL_memcpy(pixels,imagedata,x*y*n);
    SDL_UnlockTexture(texture);
    
    rect.x=100;
    rect.y=100;
    rect.w=100;
    rect.h=100;

   
    while(running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT)
            {
                running=0;
            }

            //MANAGING INPUTS ONLY BY EVENTS
            if(event.type==SDL_KEYDOWN){
                manage_inputs(&event,&rect,speed);
            }

            //MANAGING INPUTS SIMILAR TO UNITY SYSTEM
            // //will set, inside the boolean array, true (1) at the position of the key that has been pressed
            // if(event.type==SDL_KEYDOWN)
            // {
            //     KEYS[event.key.keysym.scancode]=SDL_TRUE; //use event.key.keysym.sym in order to use keyinputs as keycode and not scancode.
            // }

            // //same as before but setting it back at false
            // if(event.type==SDL_KEYUP)
            // {
            //     KEYS[event.key.keysym.scancode]=SDL_FALSE;
            // }  
            //handleinput(KEYS,&rect,&running,speed);


            //SDL_EnableKeyRepeat(); //decomment this in order to enable multiple inputs when key is kept down.
        }
        SDL_SetRenderDrawColor(Renderer,0,0,0,255);
        SDL_RenderClear(Renderer);        

        SDL_RenderCopy(Renderer,texture,NULL,&rect);

        SDL_SetRenderDrawColor(Renderer,255,0,0,255);
        SDL_RenderDrawLine(Renderer,100,100,400,400);

        SDL_SetRenderDrawColor(Renderer,0,255,0,255);
        SDL_RenderDrawLine(Renderer,200,100,300,400);

        int width,height;

        SDL_GetWindowSize(Window,&width,&height);

        SDL_RenderPresent(Renderer);
    
    }  
    SDL_Quit();
    return 0;    
}




