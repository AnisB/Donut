#version 410 

out vec4 frag_color;

uniform mat4 view; 
uniform mat4 projection;

uniform sampler2D canvas;
uniform sampler2D nbuffer;
uniform sampler2D specbuffer;
uniform sampler2D posbuffer;
uniform sampler2D depth;

uniform int width;
uniform int lenght;

in vec2 texCoord;

struct TLight
{
	vec3 position;
	vec4 diffuse;
	vec4 specular;
	float ray;
};
uniform TLight lightSource;


void main()
{
	// Fecthing albedo
	vec4 albedo = texture(canvas,texCoord);
	// Fetching normal (view space)
	vec3 normal = texture(nbuffer, texCoord).xyz;
	// Getting specularity
	float specCoeff = 1.0 - texture(specbuffer,texCoord).r;

	// Getting detph
	float profondeur = texture(depth,texCoord).r;
	if(profondeur==1.0)
	{
		// Far away => albedo
		frag_color = albedo;
		return;
	}

	// Computing light source position (view space)
	vec3 lightPos = (view*vec4(lightSource.position,1.0)).xyz;
	// Fetching xyz position (view space)
	vec3 pixelPos = texture(posbuffer,texCoord).xyz;

	// Computing the light direction
	vec3 l = lightPos - pixelPos;
	// Computing the attenuation
 	float att = clamp(1.0-length(l)/lightSource.ray,0.0,1.0)*clamp(dot(l,normal),0.0,1.0);
	// Noramlizing it
	l = normalize(l);
	// Computing the view vector
	vec3 v = normalize(-pixelPos);
	// Computing the half vector
	vec3 h = normalize(v + l);
	// Illumination coeffs
    float Idiff = 2.0*clamp(dot(l, normal),0.0,1.0);	
    float Ispec = pow(clamp(dot(h,normal),0.0,1.0),10);
    frag_color = att*(Idiff*lightSource.diffuse + Ispec*lightSource.specular);
}