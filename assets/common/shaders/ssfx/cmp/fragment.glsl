#version 410 

// Intput Data
in vec2 texCoord;

// Output data
out vec4 frag_color;

// Outputs to composite
uniform sampler2D deffered;
uniform sampler2D ssao_filtered;
uniform sampler2D albedo;
uniform sampler2D envmap;


void main()
{
	vec3 ssaoV = texture(ssao_filtered, texCoord).xyz;
	vec3 albedoV = texture(albedo, texCoord).xyz;
	vec3 envmapV = texture(envmap, texCoord).xyz;
	vec3 defferedV = texture(deffered, texCoord).xyz;

	frag_color = vec4(ssaoV * albedoV * (envmapV + defferedV) ,1.0);
}
