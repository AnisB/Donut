#version 410
uniform samplerCube skybox;

in vec3 eyeDirection;

out vec4 frag_color;

void main() 
{
	gl_FragDepth = 0.9999f;
    frag_color = texture(skybox, eyeDirection);
}