#version 410

// Input data
in layout(location=0) vec3 position;
in layout(location=1) vec3 normal;
in layout(location=2) vec2 tex_coord;

// Output data
out vec2 texCoord;


void main()
{
    gl_Position = vec4(position,1.0);
    texCoord = vec2(tex_coord.x, 1.0f - tex_coord.y);
}
