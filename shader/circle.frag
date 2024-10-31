#version 450 core

in vec2 frag_pos;
in vec4 frag_color;
in float frag_pixel_size;

out vec4 out_color;

void main() 
{
    float dist = length(frag_pos);
    if (dist > 1.0) 
    {
        discard; // Discard fragments outside circle
    }
    //float alpha = 1.0 - smoothstep(1.0 - 0.1, 1.0, dist);
    out_color = vec4(frag_color.rgb, 1.0);
}
