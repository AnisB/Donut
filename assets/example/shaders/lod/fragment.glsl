#version 410 

in vec2 txCoord;
in vec3 fnormal;

uniform sampler2D textureCmp;

out vec4 frag_color;

void main(void) 
{
    frag_color = vec4(texture(textureCmp, txCoord).xyz*fnormal,1.0);
}