#include <SDL2/SDL.h>

#include "window.hpp"
#include "primitives.hpp"
#include "movement.hpp"

int main (int argc, char** argv)
{
    Window window(WINDOW_SIZE.x, WINDOW_SIZE.y, "Rigid Body Simulation");

    Movement triangle_move(glm::vec2(0.0f, 0.0f));
    SDL_Event event;
    uint32_t last_time = SDL_GetTicks();
    bool quit = false;

    while (!quit) {
        while (window.pollEvents(event)) {
            if (event.type == SDL_QUIT) quit = true;
        }

        uint32_t currentTime = SDL_GetTicks();
        float delta_time = (currentTime - last_time) / 1000.0f;
        last_time = currentTime;

        apply_force(triangle_move, glm::vec2(0.1f, 0.0f));
        update_mov(triangle_move, delta_time);

        window.clear();

        primitives::draw_square(triangle_move.position, 0.7, {0.0, 0.0, 1.0});
        window.swapBuffers();
    }
    return 0;
}
