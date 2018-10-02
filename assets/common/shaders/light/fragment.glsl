#version 410 

// This is a gbuffer light vertex pipeline
// out color (just the light contribution)
out vec4 frag_color;

// View and projection matrices
uniform mat4 view; 
uniform mat4 projection;
uniform vec3 camera_position;

// Input Gbuffer Data
uniform sampler2D albedo;
uniform sampler2D world_normal;
uniform sampler2D specular;
uniform sampler2D world_position;
uniform sampler2D depth;

// Additional data
uniform int width;
uniform int lenght;

// input data
in vec2 texCoord;

// The light source data
struct TLight
{
	vec3 position;
	vec4 color;
	float radius;
	float power;
};

// Delcaring the light source
#define MAX_NB_LIGHTS 20
uniform TLight light_data[MAX_NB_LIGHTS];

uniform int num_lights;

void main()
{
	// Fetching normal (view space)
	vec3 ws_normal = texture(world_normal, texCoord).xyz;

	// Getting detph
	float profondeur = texture(depth, texCoord).r;
	if(profondeur > 0.999999f)
	{
		// Far away => discard
		frag_color = vec4(1.0);
		return;
	}

	vec4 finalColor = vec4(0.0,0.0,0.0,0.0);
	vec3 ws_position = texture(world_position, texCoord).xyz;
	
	for(int lIndex = 0; lIndex < num_lights; ++lIndex)
	{
		// Computing light source position (view space)
		vec3 lightPos = light_data[lIndex].position;

		// Computing the light direction
		vec3 l = lightPos - ws_position;

		// Computing the attenuation
	 	float att = clamp(1.0-length(l)/light_data[lIndex].radius,0.0,1.0)*clamp(dot(l, ws_normal),0.0,1.0);

		// Noramlizing it
		l = normalize(l);

		// Computing the view vector
		vec3 v = normalize(camera_position - ws_position);

		// Computing the half vector
		vec3 h = normalize(v + l);

		// Illumination coeffs
	    float Idiff = 2.0*clamp(dot(l, ws_normal),0.0,1.0);	
	    float Ispec = pow(clamp(dot(h, ws_normal),0.0,1.0), 10);
	    finalColor += att*(Idiff*light_data[lIndex].color + Ispec*light_data[lIndex].color);
	}
	frag_color = finalColor;
}