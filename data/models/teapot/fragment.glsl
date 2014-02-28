#version 410 


uniform sampler2D diffMap;
uniform sampler2D normalMap;

out vec4 frag_color[4];

in vec2 txCoordG;
in vec3 fnormalG;
in vec4 ecPosG;


void main()
{
    frag_color[0] = texture(normalMap,txCoordG);
    frag_color[1] = vec4(fnormalG,1.0);
    frag_color[2] = vec4(0.0);
    frag_color[3] = ecPosG;
}
