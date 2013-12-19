#version 410

uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection;
uniform mat4 modelviewprojection;

in vec3 position;


void main()
{
    gl_Position = projection*view*model*vec4(position,1.0);
    // gl_Position = modelviewprojection*vec4(position,1.0);
}
