#version 410 


uniform sampler2D diffMap;
uniform sampler2D normalMap;
out vec4 frag_color;

in vec3 fnormal;
in vec2 txCoord;

void main()
{
    //frag_color = texture(diffMap,txCoord)+vec4(fnormal,1.0)/10+texture(normalMap,txCoord);
    frag_color = texture(diffMap,txCoord);
}
