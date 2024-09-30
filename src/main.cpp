#include <SDL2/SDL.h>

#include "window.hpp"
#include "primitives.hpp"

int main (int argc, char** argv)
{
    Window window(WINDOW_SIZE.x, WINDOW_SIZE.y, "Rigid Body Simulation");

    SDL_Event event;
    bool quit = false;
    while (!quit)
    {
        while (window.pollEvents(event))
        {
            if (event.window.event == SDL_WINDOWEVENT_CLOSE) quit = true;
        }
        window.clear();
        primitives::draw_triangle({0.5, 0.5}, 0.6, {0.0, 0.0, 1.0});
        window.swapBuffers();
    }
    return 0;
}
