#version 410

// This is a gbuffer light vertex pipeline

// The full screen canvas data
// Input
in vec3 position;
in vec2 tex_coord;
// Output
out vec2 texCoord;

void main()
{
	// Mirror position
    gl_Position = vec4(position,1.0);
    // Texcoord
    texCoord = tex_coord;
}
