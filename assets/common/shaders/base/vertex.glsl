#version 410 

uniform mat4 view; 
uniform mat4 model; 
uniform mat4 projection;
uniform mat4 modelviewprojection;

// Input Data
in layout(location=0) vec3 position;
in layout(location=1) vec3 normal;
in layout(location=2) vec2 tex_coord;

// Output data
out vec2 texCoord;
out vec3 fnormal;
out vec4 ecPos;

void main()
{	
	// Output data
    gl_Position = modelviewprojection*vec4(position,1.0);
   	texCoord = tex_coord;
    fnormal = normalize(model * vec4(normal,0.0)).xyz;
	ecPos = model*vec4(position,1.0);
}
