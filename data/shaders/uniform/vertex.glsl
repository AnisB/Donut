#version 410

uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection;

in vec3 position;
in vec3 normal;
in vec2 tex_coord;

out vec4 fnormal;
out vec2 texCoord;


void main()
{
    gl_Position = projection*view*model*vec4(position,1.0);
    fnormal = vec4(normal,1.0);
    texCoord = tex_coord;
}
