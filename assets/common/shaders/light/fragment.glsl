#version 410 

// This is a gbuffer light vertex pipeline

// out color (just the light contribution)
out vec4 frag_color;

// View and projection matrices
uniform mat4 view; 
uniform mat4 projection;

// Input Gbuffer Data
uniform sampler2D albedo;
uniform sampler2D normal;
uniform sampler2D specular;
uniform sampler2D position;
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
	vec4 diffuse;
	vec4 specular;
	float ray;
};

// Delcaring the light source
#define MAX_NB_LIGHTS 20
uniform TLight lightSource[MAX_NB_LIGHTS];

uniform int nbLights;

void main()
{
	// Fetching normal (view space)
	vec3 normal = texture(normal, texCoord).xyz;
	// Fetching specularity
	float specCoeff = 1.0 - texture(specular,texCoord).r;

	// Getting detph
	float profondeur = texture(depth,texCoord).r;
	if(profondeur > 0.999f)
	{
		// Far away => discard
		frag_color = vec4(1.0);
		return;
	}

	vec4 finalColor = vec4(0.0,0.0,0.0,0.0);
	vec4 pixelPos = texture(position,texCoord);
		
	for(int lIndex = 0; lIndex < nbLights; ++lIndex)
	{
		// Computing light source position (view space)
		vec3 lightPos = (view*vec4(lightSource[lIndex].position,1.0)).xyz;
		// Fetching xyz position (view space)

		// Computing the light direction
		vec3 l = lightPos - pixelPos.xyz;
		// Computing the attenuation
	 	float att = clamp(1.0-length(l)/lightSource[lIndex].ray,0.0,1.0)*clamp(dot(l,normal),0.0,1.0);
		// Noramlizing it
		l = normalize(l);
		// Computing the view vector
		vec3 v = normalize(-pixelPos.xyz);
		// Computing the half vector
		vec3 h = normalize(v + l);
		// Illumination coeffs
	    float Idiff = 2.0*clamp(dot(l, normal),0.0,1.0);	
	    float Ispec = pow(clamp(dot(h,normal),0.0,1.0),10);
	    finalColor += att*(Idiff*lightSource[lIndex].diffuse + Ispec*lightSource[lIndex].specular);
	}
	frag_color = pixelPos.w == 1.0f ? vec4(finalColor.xyz, 1.0) : vec4(0.0);
}