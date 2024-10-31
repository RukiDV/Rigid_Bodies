#version 450 core

struct Circle {
    vec4 color;
    vec2 pos;
    float radius;
};

layout(std430, binding = 0) buffer CircleData {
    Circle circles[];
};

uniform vec2 view_position;
uniform float view_scale;
uniform vec2 screen_resolution;

out vec2 frag_pos;
out vec4 frag_color;
out float frag_pixel_size;
out vec2 circle_pos;
out float circle_radius;

void main() 
{
    const vec2 VERTICES[3] = vec2[3](
    vec2(-1.7321, -1.0),
    vec2( 1.7321, -1.0),
    vec2( 0.0,    2.0)
    );

    const Circle circle = circles[gl_InstanceID];

    float aspect = screen_resolution.y / screen_resolution.x;

    vec2 local_space = VERTICES[gl_VertexID];

    // local space to world space
    vec2 world_space = local_space * circle.radius + circle.pos;

    // world space to view space
    vec2 view_space = (world_space - view_position) / view_scale;

    // view space to clip space
    //gl_Position = vec4(local_space.x, local_space.y, 0.0, 1.0);
    gl_Position = vec4(view_space.x * aspect, view_space.y, 0.0, 1.0);

    // pass data to fragment shader
    frag_pos = local_space;
    frag_color = vec4(circle.color);
    frag_pixel_size = view_scale / (circle.radius * screen_resolution.y);
    circle_pos = circle.pos;
    circle_radius = circle.radius;
}
