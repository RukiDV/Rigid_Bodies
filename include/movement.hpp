#pragma once 

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct Movement {
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;

    Movement(glm::vec2 pos) : position(pos), velocity(0.0f), acceleration(0.0f) {}
};

void apply_force(Movement& move, const glm::vec2& force);
void update_mov(Movement& move, float delta_time);