#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <SDL2/SDL_opengl.h>

namespace primitives
{
void draw_triangle(glm::vec2 pos, float size, const glm::vec3& color);
void draw_circle(glm::vec2 pos, float radius, const glm::vec3& color);
void draw_square(glm::vec2 pos, float size, const glm::vec3& color);
} // namespace primitives
