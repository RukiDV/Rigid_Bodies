#include <GL/glew.h> 
#include <SDL2/SDL.h>
#include <vector>
#include <iostream> 
#include <random>

#include "window.hpp"
#include "primitives.hpp"
#include "movement.hpp"
#include "shader.hpp"


void circle_pos_vel(float& position, float& velocity, float radius, float boundary_min, float boundary_max) 
{
    if (position - radius < boundary_min || position + radius > boundary_max) 
    {
        velocity = -velocity;
        // correct position to within bounds
        if (position - radius < boundary_min) 
        {
            position = boundary_min + radius;
        }
        if (position + radius > boundary_max) 
        {
            position = boundary_max - radius;
        }
    }
}

void check_circle_boundaries(Movement& movement, float radius) 
{
    circle_pos_vel(movement.position.x, movement.velocity.x, radius, -1.0f, 1.0f);
    circle_pos_vel(movement.position.y, movement.velocity.y, radius, -1.0f, 1.0f);
}

void triangle_pos_vel(float& position, float& velocity, const glm::vec2 vertices[3], bool is_x_axis) {
    for (int i = 0; i < 3; ++i) {
        float vertex = is_x_axis ? vertices[i].x : vertices[i].y;
        if (vertex < -1.0f || vertex > 1.0f) 
        {
            velocity = -velocity;
            if (vertex < -1.0f) 
            {
                position += (-1.0f - vertex);
            } else if (vertex > 1.0f) 
            {
                position += (1.0f - vertex);
            }
            break;
        }
    }
}

void check_triangle_boundaries(Movement& movement, float size) 
{
    float half_size = size / 2.0f;
    glm::vec2 vertices[3] = 
    {
        {movement.position.x, movement.position.y + half_size},  // top
        {movement.position.x - half_size, movement.position.y - half_size},  // bottom left
        {movement.position.x + half_size, movement.position.y - half_size}   // bottom right
    };

    triangle_pos_vel(movement.position.x, movement.velocity.x, vertices, true);
    triangle_pos_vel(movement.position.y, movement.velocity.y, vertices, false);
}

void square_pos_vel(float& position, float& velocity, float half_size, float boundary_min, float boundary_max, const glm::vec2 vertices[4], bool is_x_axis) 
{
    for (int i = 0; i < 4; ++i) {
        float vertex = is_x_axis ? vertices[i].x : vertices[i].y;
        if (vertex < boundary_min || vertex > boundary_max) {
            velocity = -velocity;
            if (vertex < boundary_min) 
            {
                position = boundary_min + half_size;
            } else if (vertex > boundary_max) 
            {
                position = boundary_max - half_size;
            }
            break;
        }
    }
}

void check_square_boundaries(Movement& movement, float size) 
{
    float half_size = size / 2.0f;
    glm::vec2 vertices[4] = {
        {movement.position.x - half_size, movement.position.y - half_size}, // bottom left
        {movement.position.x + half_size, movement.position.y - half_size}, // bottom right
        {movement.position.x - half_size, movement.position.y + half_size}, // top left
        {movement.position.x + half_size, movement.position.y + half_size}  // top right
    };

    square_pos_vel(movement.position.x, movement.velocity.x, half_size, -1.0f, 1.0f, vertices, true);
    square_pos_vel(movement.position.y, movement.velocity.y, half_size, -1.0f, 1.0f, vertices, false);
}


int main (int argc, char** argv)
{
    Window window(WINDOW_SIZE.x, WINDOW_SIZE.y, "Rigid Body Simulation");

    Movement triangle_move(glm::vec2(0.0f, 0.0f), glm::vec2(0.1f, 0.0f));
    Movement square_move(glm::vec2(0.0f, -0.5f), glm::vec2(0.1f, 0.0f));
    
    std::vector<Movement> circle_move = 
    {
        Movement(glm::vec2(0.0f, -0.5f), glm::vec2(0.1f, 0.0f)),
        Movement(glm::vec2(0.2f, 0.5f), glm::vec2(-0.1f, 0.0f))
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
        check_circle_boundaries(circle_move[0], 0.5f);
        std::cout << "Circle position: " << circle_move[0].position.x << ", " << circle_move[0].position.y << std::endl; 

        apply_force(circle_move[1], glm::vec2(-0.1f, 0.0f));
        update_mov(circle_move[1], delta_time);
        check_circle_boundaries(circle_move[1], 0.2f);
        std::cout << "Circle position: " << circle_move[1].position.x << ", " << circle_move[1].position.y << std::endl; 

        apply_force(triangle_move, glm::vec2(0.5f, 0.0f));
        update_mov(triangle_move, delta_time);
        check_triangle_boundaries(triangle_move, 0.2f);
        std::cout << "Triangle position: " << triangle_move.position.x << ", " << triangle_move.position.y << std::endl;

        apply_force(square_move, glm::vec2(0.2f, 0.0f));
        update_mov(square_move, delta_time);
        check_square_boundaries(square_move, 0.3f);
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

        primitives::draw_triangle(triangle_move.position, 0.2, {0.0, 0.0, 1.0});
        primitives::draw_square(square_move.position, 0.3, {0.0, 1.0, 1.0});

        window.swapBuffers();
    }
    return 0;
}
