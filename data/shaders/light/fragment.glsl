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

	vec4 diffColor = texture(canvas,texCoord);
	vec3 normal = texture(nbuffer,texCoord).xyz;
	normal = (normal-vec3(0.5))*2.0;
	normal = normalize(normal);

	float specCoeff = 1.0-texture(specbuffer,texCoord).r;
	float profondeur = texture(depth,texCoord).r;
	if(profondeur==1.0)
	{
		frag_color= diffColor;
		return;
	}
	vec3 lightPos = (view*vec4(lightSource.position,1.0)).xyz;
	vec4 pixelPosFull = texture(posbuffer,texCoord);
	pixelPosFull = (pixelPosFull-vec4(0.5,0.5,0.5,0.0))*2.0;

	vec3 pixelPos = (pixelPosFull/pixelPosFull.w).xyz;
	vec3 l = lightPos-pixelPos;
 	float att = clamp(1.0-length(l)/lightSource.ray,0.0,1.0)*clamp(dot(l,normal),0.0,1.0);
	l = normalize(l);
	vec3 v = normalize(-pixelPos);
	vec3 h = normalize(v + l);

    float Idiff = clamp(dot(l,normal),0.0,1.0);	
    float Ispec = pow(clamp(dot(h,normal),0.0,1.0),10);

    frag_color = att*(Idiff*lightSource.diffuse + Ispec*lightSource.specular);
}