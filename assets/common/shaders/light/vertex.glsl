#version 410

// This is a gbuffer light vertex pipeline

// The full screen canvas data
// Input
in layout(location=0) vec3 position;
in layout(location=1) vec3 normal;
in layout(location=2) vec2 tex_coord;
// Output
out vec2 texCoordV;

void main()
{
	// Mirror position
    gl_Position = vec4(position,1.0);
    // Texcoord
    texCoordV = tex_coord;
}
