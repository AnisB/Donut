#version 410

// Texture sampler
uniform vec4 uniform_color;

// reflection data
uniform float reflection = 0.0;
// Output Gbuffer
out vec4 frag_color[4];

// Input data
in vec2 f_tex_coord;
in vec3 f_normal;
in vec4 f_eye_pos;

void main()
{
	// Outputing in the Zbuffer
    frag_color[0] = vec4(uniform_color); // Albedo
    frag_color[1] = vec4(f_normal,1.0); // Camera space normal
    frag_color[2] = vec4(0.0,0.0,reflection,1.0); // Specularity (sun contribution and reflectivity)
    frag_color[3] = vec4(f_eye_pos.xyz, 1.0f); // Camera space position
}
