#version 410 

out vec4 frag_color;

in vec4 fnormal;
in vec2 texCoord;

void main()
{
    frag_color = fnormal*texCoord.y*texCoord.x;
}
