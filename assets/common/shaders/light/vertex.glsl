#version 410

// This is a gbuffer light vertex pipeline

// The full screen canvas data
// Input
in vec3 position;
in vec3 normal;
in vec2 tex_coord;
// Output
out vec2 texCoordV;

void main()
{
	// Mirror position
    gl_Position = vec4(position,1.0);
    // Texcoord
    texCoordV = tex_coord;
}
