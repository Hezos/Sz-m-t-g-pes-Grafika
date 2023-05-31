#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "sddl.h"
#include "D:\Számítógépes grafika\c_sdk_220203\c_sdk_220203\MinGW\include\SDL2\SDL.h"
#include "D:\Számítógépes grafika\c_sdk_220203\c_sdk_220203\MinGW\include\SDL2\SDL_render.h"
#include "stdbool.h"

typedef struct Line
{
    int StartX;
    int StartY;
    int EndX;
    int EndY;
    char color[];
} Line;

int main(void){
    //Pillér Gitlab
    SDL_Window* window = SDL_CreateWindow("Hello SDL!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* SDLrenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Line vonal;
    int clickCount = 0;
    SDL_MouseButtonEvent MouseEvent;

    int MAX_LINE_COUNT = 6;

    for (size_t i = 0; i < MAX_LINE_COUNT; i++)
    {
        while (SDL_PollEvent(&MouseEvent))
        {
            switch (MouseEvent.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    printf("X position: %d, Y position: %d", MouseEvent.x, MouseEvent.y);
                    vonal.StartX = MouseEvent.x;
                    vonal.StartY = MouseEvent.y;
                    break;
                case SDL_MOUSEBUTTONUP:
                    vonal.EndX = MouseEvent.x;
                    vonal.EndY = MouseEvent.y;
                    // vonal.color = "black";
                    SDL_SetRenderDrawColor(SDLrenderer, 34, 123, 20, SDL_ALPHA_OPAQUE);
                    SDL_RenderDrawLine(SDLrenderer, vonal.StartX, vonal.StartY, vonal.EndX, vonal.StartY);
                   break;
                default:
                    break;
            }
        }   
    }
    
    
    


    //Szín beállítása RGB-vel
    SDL_SetRenderDrawColor(SDLrenderer, 0,0,0,SDL_ALPHA_OPAQUE);
    //Rajzfelület letisztítása:
    SDL_RenderClear(SDLrenderer);
    for (int i = 0; i < 255; i++)
    {
        //Rajz más színekkel?
       SDL_SetRenderDrawColor(SDLrenderer, 255, i, 0, SDL_ALPHA_OPAQUE);
       SDL_RenderDrawLine(SDLrenderer, 10,10, 500, i*2);
    }
    //Jelenlévő állapot kirajzolása:
    SDL_RenderPresent(SDLrenderer);

    // 2 kattintás
    //SDL_RenderDrawLine(SDLrenderer, );

    SDL_Delay(5000);
    SDL_DestroyRenderer(SDLrenderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;     
}