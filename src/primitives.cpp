#include <GL/glew.h>
#include <GL/gl.h>
#include <cmath>
#include <glm/glm.hpp>
#include <vector>

#include "primitives.hpp"
#include "shader.hpp"

namespace primitives
{

GLuint ssbo;
Shader* circle_shader = nullptr;
uint32_t circle_count = 0;

std::vector<Circle> circles = 
{
    Circle{glm::vec4(1.0, 0.0, 1.0, 1.0), glm::vec2(0.0f, -0.5f), 0.2f},
    Circle{glm::vec4(0.0, 1.0, 1.0, 1.0), glm::vec2(0.2f, 0.5f), 0.2f}
};

void init_circle()
{
    circle_count = circles.size();

    glGenBuffers(1, &ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, circles.size() * sizeof(Circle), circles.data(), GL_STATIC_READ);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    circle_shader = new Shader("circle.vert", "circle.frag");
}

void update_circle()
{    
    // update SSBO with new data
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, circles.size() * sizeof(Circle), circles.data(), GL_STATIC_READ);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void draw_circle()
{
    circle_shader->use_shader();

    // set uniform variables for shader
    GLint view_position = glGetUniformLocation(circle_shader->get_program_id(), "view_position");
    GLint view_scale = glGetUniformLocation(circle_shader->get_program_id(), "view_scale");
    GLint screen_resolution = glGetUniformLocation(circle_shader->get_program_id(), "screen_resolution");

    // set static values for now
    glUniform2f(view_position, 0.0f, 0.0f);
    glUniform1f(view_scale, 1.0f);
    glUniform2f(screen_resolution, 1200.0f, 1200.0f);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);

    glDrawArraysInstanced(GL_TRIANGLES, 0, 3, circle_count);
}

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

std::vector<Circle>& get_circles() 
{
    return circles;
}

void set_circles(const std::vector<Circle>& new_circles)
{
    circles = new_circles;
    update_circle();
}

} // namespace primitives
