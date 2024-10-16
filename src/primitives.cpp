#include "primitives.hpp"

#include <cmath>

namespace primitives
{
void draw_triangle(glm::vec2 pos, float size, const glm::vec3& color)
{
    const float half_size = size / 2.0f;
    glBegin(GL_TRIANGLES);
    glColor3f(color.r, color.g, color.b);
    glVertex2f(pos.x, pos.y + half_size);
    glVertex2f(pos.x - half_size, pos.y - half_size);
    glVertex2f(pos.x + half_size, pos.y - half_size);
    glEnd();
}

void draw_circle(glm::vec2 pos, float radius, const glm::vec3& color)
{
    const int num_segments = 100;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(color.r, color.g, color.b);
    // center circle
    glVertex2f(0.0f, 0.0f);

    for (int i = 0; i <= num_segments; i++) {
        float angle = 2.0f * M_PI * float(i) / float(num_segments);
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(dx, dy);
    }
    glEnd();
}

void draw_square(glm::vec2 pos, float size, const glm::vec3& color)
{
    const float half_size = size / 2.0f;
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(color.r, color.g, color.b);
    glVertex2f(pos.x + half_size, pos.y + half_size);
    glVertex2f(pos.x - half_size, pos.y + half_size);
    glVertex2f(pos.x + half_size, pos.y - half_size);
    glVertex2f(pos.x - half_size, pos.y - half_size);
    glEnd();
}
} // namespace primitives
