#include "app.h"
#include "stdbool.h"
#include <stdio.h>
#include "time.h"
#include <SDL2/SDL_image.h>
/**
 * Main function
 */
bool moving = false;
int main(int argc, char* argv[])
{
    App app;

    init_app(&app, 1500, 800);
    while (app.is_running) {
        handle_app_events(&app);
        update_app(&app);
        /*
        SDL_Event event;
        if (moving == true)
        {
                       
        }else{
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_B:
                        StartMoving();
                        break;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
            }
        }
                */            
         render_app(&app);
    }
    destroy_app(&app);
    return 0;
}
void StartMoving(){
    moving = true;
}
