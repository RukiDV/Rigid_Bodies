#include "primitives.hpp"

namespace primitives
{
void draw_triangle(glm::vec2 pos, float size, const glm::vec3& color)
{
    glBegin(GL_TRIANGLES);
    glColor3f(color.r, color.g, color.b);
    glVertex2f(-pos.x * size, -pos.y * size);
    glVertex2f(pos.x * size, -pos.y * size);
    glVertex2f(pos.x * size, pos.y * size);
    glEnd();
}
} // namespace primitives
