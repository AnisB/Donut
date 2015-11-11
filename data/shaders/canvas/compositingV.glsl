#version 410

// Input Data
in vec3 position;
in vec2 tex_coord;

// Output Data
out vec2 texCoord;


void main()
{
	// Simple fullscreen rasterisaiton
    gl_Position = vec4(position,1.0);
    texCoord = tex_coord;
}
