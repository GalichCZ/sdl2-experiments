#include "window.h"
#include <deque>
#include <algorithm>

enum Direction
{
    DOWN,
    LEFT,
    RIGHT,
    UP
};
SDL_Rect head{500, 500, 10, 10};
int dir = 0;
std::deque<SDL_Rect> rq;
int size;

class Snake
{
    Window window;

public:
    Snake()
    {
        size = 1;
    }

    void borderCheck()
    {
        if (head.x == WIDTH)
        {
            head.x = 10;
        }
        if (head.x == 0)
        {
            head.x = WIDTH - 10;
        }
        if (head.y == 0)
        {
            head.y = HEIGHT - 10;
        }
        if (head.y == HEIGHT)
        {
            head.y = 10;
        }
    }

    void directionCheck()
    {
        switch (dir)
        {
        case DOWN:
            head.y += 10;
            break;
        case LEFT:
            head.x -= 10;
            break;
        case RIGHT:
            head.x += 10;
            break;
        case UP:
            head.y -= 10;
            break;
        default:
            break;
        }
    }

    void snakeRender()
    {
        int index = 0;
        std::for_each(rq.begin(), rq.end(), [&](auto snake_segment)
                      { 
                        window.setColor(index);
                        window.fillSegment(snake_segment);
                        index++; });
    }

    void checkSnakeBump()
    {
        std::for_each(rq.begin(), rq.end(), [&](auto &snake_segment)
                      {
            if(head.x == snake_segment.x && head.y == snake_segment.y)
            {
                size = 1;
            } });
    }
};