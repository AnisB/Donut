#version 410 


uniform sampler2D diffMap;
uniform sampler2D normalMap;

out vec4 frag_color[3];

in vec2 txCoord;
in float depthCmp;
in vec3 fnormal;


void main()
{
    frag_color[0] = texture(diffMap,txCoord);
    frag_color[1] = vec4(0.0);
    frag_color[2] = vec4(fnormal,1.0);
}
