#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include <deque>
#include <iostream>
#include "window.h"
#include "snake.h"

int main()
{
    Window windowShow;
    Snake snake;

    auto window = SDL_CreateWindow("Snake", X_POS, Y_POS, WIDTH, HEIGHT, 0);
    auto renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event e;

    // int size = 1;

    std::vector<SDL_Rect> apples;

    for (int i = 0; i < 100; i++)
    {
        apples.emplace_back(rand() % 100 * 10, rand() % 100 * 10, 10, 10);
    }

    bool running = true;

    while (running)
    {
        windowShow.renderWindow();
        snake.borderCheck();
        snake.directionCheck();
        snake.snakeRender();
        snake.checkSnakeBump();

        std::for_each(apples.begin(), apples.end(), [&](auto &apple)
                      { 
            if (head.x == apple.x && head.y == apple.y)
            {
              size += 10;
              apple.x = -10;
              apple.y = -10;
            } });

        rq.push_front(head);

        while (rq.size() > size)
        {
            rq.pop_back();
        }

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
            }
            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_DOWN && dir != UP)
                {
                    dir = DOWN;
                }
                if (e.key.keysym.sym == SDLK_LEFT && dir != RIGHT)
                {
                    dir = LEFT;
                }
                if (e.key.keysym.sym == SDLK_RIGHT && dir != LEFT)
                {
                    dir = RIGHT;
                }
                if (e.key.keysym.sym == SDLK_UP && dir != DOWN)
                {
                    dir = UP;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);
        std::for_each(apples.begin(), apples.end(), [&](auto apple)
                      { SDL_RenderFillRect(renderer, &apple); });

        SDL_RenderPresent(renderer);
        SDL_Delay(25);
    }

    return 0;
}