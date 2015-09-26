#version 410 

out vec4 frag_color[4];

in vec3 fnormalG;

void main()
{
    frag_color[0] = vec4(1.0,1.0,1.0,1.0);
    frag_color[1] = vec4(fnormalG,1.0);
    frag_color[2] = vec4(0.0,1.0,0.0,1.0);
    frag_color[3] = vec4(0.0,0.0,1.0,1.0);
}
