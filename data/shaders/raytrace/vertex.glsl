#version 410

uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection;
uniform mat4 modelviewprojection;

in vec3 position;
in vec3 normal;
in vec2 tex_coord;

out vec2 texCoord;
out vec4 unitX;
out vec4 unitY;
out vec4 coinInfGauche;
out vec3 cameraPosition;

#define focalDistance 50.0f
const float hauteurEcran = 1.52638111*focalDistance;
const float ratio = 1280.0/720.0;

void main()
{
	cameraPosition = view[3].xyz;
	unitX = normalize(view * vec4(1.0,0.0,0.0,0.0));
	unitY = normalize(view * vec4(0.0,1.0,0.0,0.0));
	vec4 unitZ = normalize(view * vec4(0.0,0.0,1.0,0.0));
	coinInfGauche = -unitZ * 50.0 - unitX*hauteurEcran*ratio - unitY*hauteurEcran;
	// cameraPosition = vec3(0.0,0.0,10.0);
	// cameraPosition = vec3(view[0][3],view[1][3],view[2][3]);
    gl_Position = vec4(position,1.0);
    // gl_Position = modelviewprojection*vec4(position,1.0);
    texCoord = tex_coord;
}
