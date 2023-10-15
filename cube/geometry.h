#include "screen.h"
#include <numeric>
#include <iostream>

struct vec3
{
    float x, y, z;
};

struct connection
{
    int a, b;
};

class Geometry
{

private:
    void rotate(vec3 &point, float x = 1, float y = 1, float z = 1)
    {
        float rad = 0;

        rad = x;
        point.y = std::cos(rad) * point.y - std::sin(rad) * point.z;
        point.z = std::sin(rad) * point.y + std::cos(rad) * point.z;

        rad = y;
        point.x = std::cos(rad) * point.x + std::sin(rad) * point.z;
        point.z = -std::sin(rad) * point.x + std::cos(rad) * point.z;

        rad = z;
        point.x = std::cos(rad) * point.x - std::sin(rad) * point.y;
        point.y = std::sin(rad) * point.x + std::cos(rad) * point.y;
    }

    void line(Screen &screen, float x1, float y1, float x2, float y2)
    {
        float dx = x2 - x1;
        float dy = y2 - y1;

        float length = std::sqrt(dx * dx + dy * dy);
        float angle = std::atan2(dy, dx);

        for (float i = 0; i < length; i++)
        {
            screen.pixel(x1 + std::cos(angle) * i, y1 + std::sin(angle) * i);
        }
    }
    vec3 centeroid(vec3 &c, std::vector<vec3> &points)
    {
        for (auto &p : points)
        {
            c.x += p.x;
            c.y += p.y;
            c.z += p.z;
        }

        c.x /= points.size();
        c.y /= points.size();
        c.z /= points.size();

        return c;
    };

public:
    void Cube(float distanceMult)
    {
        std::cout << distanceMult;
        Screen screen;
        std::vector<vec3> points{
            {100 * distanceMult, 100 * distanceMult, 100 * distanceMult},
            {200 * distanceMult, 100 * distanceMult, 100 * distanceMult},
            {200 * distanceMult, 200 * distanceMult, 100 * distanceMult},
            {100 * distanceMult, 200 * distanceMult, 100 * distanceMult},

            {100 * distanceMult, 100 * distanceMult, 200 * distanceMult},
            {200 * distanceMult, 100 * distanceMult, 200 * distanceMult},
            {200 * distanceMult, 200 * distanceMult, 200 * distanceMult},
            {100 * distanceMult, 200 * distanceMult, 200 * distanceMult},
        };

        std::vector<connection> connections{
            {0, 4},
            {1, 5},
            {2, 6},
            {3, 7},

            {0, 1},
            {1, 2},
            {2, 3},
            {3, 0},

            {4, 5},
            {5, 6},
            {6, 7},
            {7, 4},
        };

        std::vector<SDL_Color> faceColors{
            {255, 0, 0, 255},   // red
            {0, 255, 0, 255},   // green
            {0, 0, 255, 255},   // blue
            {255, 255, 0, 255}, // yellow
            {0, 255, 255, 255}, // cyan
            {255, 0, 255, 255}  // magenta
        };

        vec3 c{0, 0, 0};
        c = centeroid(c, points);

        while (true)
        {
            for (auto &p : points)
            {
                p.x -= c.x;
                p.y -= c.y;
                p.z -= c.z;
                rotate(p, 0.004, 0.002, 0.008);
                p.x += c.x;
                p.y += c.y;
                p.z += c.z;
                screen.pixel(p.x, p.y);
            }

            for (auto &conn : connections)
            {
                line(screen, points[conn.a].x, points[conn.a].y, points[conn.b].x, points[conn.b].y);
            }

            screen.show();
            screen.clear();
            screen.input();
            SDL_Delay(30);
        }
    }
};