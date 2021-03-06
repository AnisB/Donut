#version 410

// Zbuffer data
uniform float fcoef;

// Output Gbuffer
out vec4 frag_color[4];

// Input data
in vec2 texCoord;
in vec3 fnormal;
in vec4 ecPos;
in float flogz;


void main()
{
	// Outputing in the Zbuffer
    frag_color[0] = vec4(1.0,1.0,1.0,1.0); // Albedo
    frag_color[1] = vec4(fnormal,1.0); // Camera space normal
    frag_color[2] = vec4(texCoord, 1.0, 1.0); // Specularity (sun contribution and reflectivity)
    frag_color[3] = vec4(ecPos.xyz, 1.0f); // Camera space position
}