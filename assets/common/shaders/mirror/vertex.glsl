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
out vec2 texCoordV;
out vec3 fnormalV;
out vec4 ecPosV;
out float flogzG;

void main()
{	
	// Output data
    gl_Position = modelviewprojection*vec4(position,1.0);
   	texCoordV = tex_coord;
    fnormalV = normalize(view*model*vec4(normal,0.0)).xyz;
	ecPosV = view*model*vec4(position,1.0);

    // Logarithmic depth buffer
    gl_Position.z = log2(max(1e-6, 1.0 + gl_Position.w)) * fcoef - 1.0;
    flogzG = 1.0 + gl_Position.w;
}
