#version 410

// Texture sampler
uniform sampler2D color_tex;
uniform sampler2D rm_tex;

// reflection data
uniform float reflection = 0.0;

// Output Gbuffer
out vec4 frag_color[4];

// Input data
in vec2 texCoord;
in vec3 fnormal;
in vec4 ecPos;

void main()
{	
	// Read the textures
	vec4 color = texture(color_tex, texCoord);
	vec4 rm = texture(rm_tex, texCoord);

	// Outputing in the Zbuffer
    frag_color[0] = color;
    frag_color[1] = vec4(fnormal, 1.0);
    frag_color[2] = vec4(rm.xy, reflection, 1.0); // Specularity (sun contribution and reflectivity)
    frag_color[3] = vec4(ecPos.xyz, 1.0f); // Camera space position
}
