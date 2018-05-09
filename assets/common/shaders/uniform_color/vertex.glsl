#version 410

// Scenes matrices
uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection;
uniform mat4 modelviewprojection;

//Logarithmic depth buffer
uniform float fcoef;

// Input Data
in layout(location=0) vec3 position;
in layout(location=1) vec3 normal;
in layout(location=2) vec2 tex_coord;

// Output data
out vec2 f_tex_coord;
out vec3 f_normal;
out vec4 f_eye_pos;
out float f_logz;

void main()
{	
	// Output data
    gl_Position = modelviewprojection*vec4(position,1.0);
   	f_tex_coord = tex_coord;
    f_normal = normalize(view*model*vec4(normal,0.0)).xyz;
	f_eye_pos = view*model*vec4(position,1.0);
}
