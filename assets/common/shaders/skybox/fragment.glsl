#version 410
uniform samplerCube skybox;

in vec3 eyeDirection;

out vec4 frag_color[4];

void main() 
{
	gl_FragDepth  = 0.99999f;
    frag_color[0] = texture(skybox, eyeDirection);
    frag_color[1] = vec4(0.0,0.0, 1.0, 1.0);
    frag_color[2] = vec4(0.0,0.0,0.0, 1.0);
    frag_color[3] = vec4(0.0,0.0, 0.0f, 0.0f);
}