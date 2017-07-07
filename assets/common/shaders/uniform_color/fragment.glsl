#version 410

// Texture sampler
uniform vec4 uniform_color;
// Zbuffer data
uniform float fcoef;

// reflection data
uniform float reflection = 0.0;
// Output Gbuffer
out vec4 frag_color[4];

// Input data
in vec2 texCoord;
in vec3 fnormal;
in vec4 ecPos;
in float flogz;


void main()
{
	// logarithmic zbuffer
	gl_FragDepth = 0.5 * log2(flogz) * fcoef;
	// Outputing in the Zbuffer
    frag_color[0] = uniform_color; // Albedo
    frag_color[1] = vec4(fnormal,1.0); // Camera space normal
    frag_color[2] = vec4(0.0,0.0,reflection,1.0); // Specularity (sun contribution and reflectivity)
    frag_color[3] = ecPos; // Camera space position
}
