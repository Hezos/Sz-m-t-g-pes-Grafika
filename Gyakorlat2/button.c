#include "D:\Számítógépes grafika\c_sdk_220203\c_sdk_220203\MinGW\include\SDL2\SDL.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

SDL_Window *window;
SDL_Renderer *renderer;

typedef struct {
    SDL_Rect rect;
    SDL_Color color;
    SDL_Texture *texture;
    SDL_bool hovered;
} Button;

Button createButton(SDL_Rect rect, SDL_Color color) {
    Button button;
    button.rect = rect;
    button.color = color;
    button.hovered = SDL_FALSE;
    return button;
}

void drawButton(Button button) {
    SDL_SetRenderDrawColor(renderer, button.color.r, button.color.g, button.color.b, button.color.a);
    SDL_RenderFillRect(renderer, &button.rect);
}

void handleButtonEvents(Button *button, SDL_Event event) {
    switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                if (SDL_PointInRect(&event.button, &button->rect)) {
                    // handle button click event
                }
            }
            break;
        case SDL_MOUSEMOTION:
            if (SDL_PointInRect(&event.motion, &button->rect)) {
                button->hovered = SDL_TRUE;
            } else {
                button->hovered = SDL_FALSE;
            }
            break;
        default:
            break;
    }
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Button Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_bool quit = SDL_FALSE;

    SDL_Color buttonColor = {100, 100, 100, 255};
    SDL_Rect buttonRect = {50, 50, 100, 50};
    Button button = createButton(buttonRect, buttonColor);

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = SDL_TRUE;
            }

            handleButtonEvents(&button, event);
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        drawButton(button);

        if (button.hovered) {
            SDL_SetWindowTitle(window, "Button Example - Hovered");
        } else {
            SDL_SetWindowTitle(window, "Button Example");
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}