#version 410 

out vec4 frag_color;

in vec3 fnormal;
in vec2 texCoord;

void main()
{
    frag_color = vec4(fnormal,1.0)*texCoord.y*texCoord.x;
}
