#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <SDL2/SDL_opengl.h>

#include "movement.hpp"

namespace primitives
{

struct Circle
{
    glm::vec4 color;
    glm::vec2 pos;
    alignas(8) float radius;
};
void init_circle();
void update_circle();
void draw_circle();
void draw_triangle(glm::vec2 pos, float size, const glm::vec3& color);
void draw_square(glm::vec2 pos, float size, const glm::vec3& color);
std::vector<Circle>& get_circles();
void set_circles(const std::vector<Circle>& new_circles);
void circle_pos_vel(float& position, float& velocity, float radius, float boundary_min, float boundary_max);
void check_circle_boundaries(Movement& movement, float radius);
void check_triangle_boundaries(Movement& movement, float size);
void square_pos_vel(float& position, float& velocity, float half_size, float boundary_min, float boundary_max, const glm::vec2 vertices[4], bool is_x_axis);
void check_square_boundaries(Movement& movement, float size);
} // namespace primitives
