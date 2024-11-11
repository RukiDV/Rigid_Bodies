#pragma once 

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct Movement {
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    float rotation;
    float angular_velocity;

    Movement(glm::vec2 pos, glm::vec2 vel) : position(pos), velocity(vel), acceleration(0.0f), rotation(0.0f), angular_velocity(0.0f) {}
};

void apply_force(Movement& move, const glm::vec2& force);
void update_mov(Movement& move, float delta_time);