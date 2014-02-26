#version 410

out vec4 frag_color[3];

in vec2 texCoord;
in vec3 fnormal;


void main()
{
    frag_color[0]= vec4(texCoord,0.8,1.0);
    frag_color[1] = vec4(fnormal,1.0);
    frag_color[2] = vec4(0.0);
}
