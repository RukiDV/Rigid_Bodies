#include <GL/glew.h> 
#include <SDL2/SDL.h>
#include <vector>
#include <iostream> 
#include <random>

#include "window.hpp"
#include "primitives.hpp"
#include "movement.hpp"
#include "shader.hpp"

int main (int argc, char** argv)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    Window window(WINDOW_SIZE.x, WINDOW_SIZE.y, "Rigid Body Simulation");

    Movement triangle_move(glm::vec2(0.0f, 0.0f), glm::vec2(dist(gen), dist(gen)));
    Movement square_move(glm::vec2(0.0f, -0.5f), glm::vec2(dist(gen), dist(gen)));
    
    std::vector<Movement> circle_move = 
    {
        Movement(glm::vec2(0.0f, -0.5f), glm::vec2(dist(gen), dist(gen))),
        Movement(glm::vec2(0.2f, 0.5f), glm::vec2(dist(gen), dist(gen)))
    };

    SDL_Event event;
    uint32_t last_time = SDL_GetTicks();
    bool quit = false;

    primitives::init_circle();
    while (!quit) {
        while (window.pollEvents(event)) 
        {
            if (event.type == SDL_QUIT) quit = true;
        }

        uint32_t currentTime = SDL_GetTicks();
        float delta_time = (currentTime - last_time) / 1000.0f;
        last_time = currentTime;

        apply_force(circle_move[0], glm::vec2(0.1f, 0.0f));
        update_mov(circle_move[0], delta_time);
        primitives::check_circle_boundaries(circle_move[0], 0.5f);
        std::cout << "Circle position: " << circle_move[0].position.x << ", " << circle_move[0].position.y << std::endl; 

        apply_force(circle_move[1], glm::vec2(-0.1f, 0.0f));
        update_mov(circle_move[1], delta_time);
        primitives::check_circle_boundaries(circle_move[1], 0.2f);
        std::cout << "Circle position: " << circle_move[1].position.x << ", " << circle_move[1].position.y << std::endl; 

        apply_force(triangle_move, glm::vec2(0.5f, 0.0f));
        update_mov(triangle_move, delta_time);
        primitives::check_triangle_boundaries(triangle_move, 0.2f);
        std::cout << "Triangle position: " << triangle_move.position.x << ", " << triangle_move.position.y << std::endl;

        apply_force(square_move, glm::vec2(0.2f, 0.0f));
        update_mov(square_move, delta_time);
        primitives::check_square_boundaries(square_move, 0.3f);
        std::cout << "Square position: " << square_move.position.x << ", " << square_move.position.y << std::endl;

         // update circles with new positions
        auto& circles = primitives::get_circles();
        circles[0].pos = circle_move[0].position;
        circles[0].radius = 0.5;
        circles[0].color = glm::vec4{1.0, 0.0, 1.0, 1.0};
        circles[1].pos = circle_move[1].position;
        circles[1].radius = 0.2;
        primitives::update_circle();
    
        window.clear();

        primitives::draw_circle();

        // unbind vao and shader to prevent interference with immediate mode drawing
        glBindVertexArray(0);
        glUseProgram(0);

        primitives::draw_triangle(triangle_move.position, 0.2, {0.5, 0.0, 1.0});
        primitives::draw_square(square_move.position, 0.4, {0.0, 0.6, 1.0});

        window.swapBuffers();
    }
    return 0;
}
