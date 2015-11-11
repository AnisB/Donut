#version 410

// Input data
in vec3 position;
in vec3 normal;
in vec2 tex_coord;

// Output data
out vec2 texCoord;


void main()
{
    gl_Position = vec4(position,1.0);
    texCoord = tex_coord;
}
