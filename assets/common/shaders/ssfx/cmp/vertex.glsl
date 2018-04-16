#version 410

// Input Data
in layout(location=0) vec3 position;
in layout(location=1) vec3 normal;
in layout(location=2) vec2 tex_coord;

// Output Data
out vec2 texCoord;


void main()
{
	// Simple fullscreen rasterisaiton
    gl_Position = vec4(position,1.0);
    texCoord = tex_coord;
}
