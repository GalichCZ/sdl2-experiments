#include <SDL2/SDL.h>

#pragma once

const int X_POS = 0;
const int Y_POS = 0;
const int WIDTH = 1000;
const int HEIGHT = 1000;

class Window
{
    SDL_Renderer *renderer;
    SDL_Event e;
    SDL_Window *window;

public:
    Window()
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        window = SDL_CreateWindow("Snake", X_POS, Y_POS, WIDTH, HEIGHT, 0);
        renderer = SDL_CreateRenderer(window, -1, 0);
    }

    void renderWindow()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    };

    void setColor(int index)
    {
        index % 2 == 0 ? SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255) : SDL_SetRenderDrawColor(renderer, 3, 201, 169, 255);
    }

    void fillSegment(auto snake_segment)
    {
        SDL_RenderFillRect(renderer, &snake_segment);
    }
};