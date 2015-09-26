#version 410

uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection;
uniform mat4 modelviewprojection;

in vec3 position;

out vec3 ecPos;

void main()
{
    vec3 realPos = position*100.0;
    gl_Position = modelviewprojection*vec4(realPos,1.0);
    ecPos = (view*model*vec4(realPos,1.0)).xyz;
}
