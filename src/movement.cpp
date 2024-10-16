#include "movement.hpp"

void apply_force(Movement& move, const glm::vec2& force) {
    const float mass = 1.0f;
    move.acceleration += force / mass;
}

void update_mov(Movement& move, float delta_time) {
    move.velocity += move.acceleration * delta_time;
    move.position += move.velocity * delta_time;
    move.acceleration = glm::vec2(0.0f);
}
