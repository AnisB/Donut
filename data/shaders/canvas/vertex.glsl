#version 410

in vec3 position;
in vec2 tex_coord;

out vec2 texCoord;


void main()
{
    gl_Position = vec4(position,1.0);
    texCoord = tex_coord;
}
