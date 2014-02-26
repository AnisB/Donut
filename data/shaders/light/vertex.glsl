#version 410

uniform mat4 view; 
uniform mat4 projection;

in vec3 position;
in vec2 tex_coord;

out vec2 texCoordV;

void main()
{
    gl_Position = vec4(position,1.0);
    texCoordV = tex_coord;
}
