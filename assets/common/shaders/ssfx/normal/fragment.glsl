#version 410 

// Input data
in vec2 texCoord;

// Out data
out vec4 frag_color;

// Input uniforms
uniform sampler2D normal;

void main()
{ 
    frag_color = texture(normal, texCoord);
}
