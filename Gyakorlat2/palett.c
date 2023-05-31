#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "sddl.h"
#include "D:\Számítógépes grafika\c_sdk_220203\c_sdk_220203\MinGW\include\SDL2\SDL.h"
#include "D:\Számítógépes grafika\c_sdk_220203\c_sdk_220203\MinGW\include\SDL2\SDL_render.h"
#include "stdbool.h"

int main(void){

    SDL_MouseButtonEvent MouseEvent;
    SDL_Window* window = SDL_CreateWindow("Hello SDL!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* SDLrenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Rect rectangles[3];
    while (SDL_PollEvent(&MouseEvent))
    {
       switch (MouseEvent.type)
       {
       case SDL_MOUSEBUTTONDOWN:
            printf("X position: %d, Y position: %d", MouseEvent.x, MouseEvent.y);
            SDL_Point point = {MouseEvent.x, MouseEvent.y};
            for (int i = 0; i < 3; i++)
            {  
                if (SDL_PointInRect(&point, &rectangles[i]))
                {
                    //We got a click
                 SDL_Palette* palette = SDL_AllocPalette(3);
                SDL_SetRenderDrawColor(SDLrenderer, palette->colors[i].r, palette->colors[i].g, palette->colors[i].b, palette->colors[i].a);
                }    
            }
            
            
        break;
       case SDL_MOUSEBUTTONUP:
            SDL_Color colors[3];
            SDL_Palette* palette = SDL_AllocPalette(3);
            SDL_SetPaletteColors(&palette, colors, 0, 3);

            for (size_t i = 0; i < 3; i++)
            {
                rectangles[i] = {10,20};
            }
            
            for (size_t i = 0; i < 3; i++)
            {
            SDL_RenderDrawPoint(10,(20*(i+1)));
             SDL_SetRenderDrawColor(SDLrenderer, palette->colors[i].r, palette->colors[i].g, palette->colors[i].b, palette->colors[i].a);
             SDL_RenderDrawRect(SDLrenderer,&rectangles[i]);
             SDL_RenderFillRect(SDLrenderer, &rectangles[i]);  
            }
            
        break;
       default:
        break;
       }
    }

    return 0;
}