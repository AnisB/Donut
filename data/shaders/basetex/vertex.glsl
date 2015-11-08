#version 410

uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection;
uniform mat4 modelviewprojection;
uniform float fcoef;

in vec3 position;
in vec3 normal;
in vec2 tex_coord;

out vec2 texCoordV;
out vec3 fnormalV;
out vec4 ecPosV;
out float flogzG;

void main()
{	
	ecPosV = view*model*vec4(position,1.0);
    gl_Position = modelviewprojection*vec4(position,1.0);
    gl_Position.z = log2(max(1e-6, 1.0 + gl_Position.w)) * fcoef - 1.0;
    flogzG = 1.0 + gl_Position.w;
    texCoordV = tex_coord;
    fnormalV = normalize(view*model*vec4(normal,0.0)).xyz;
}
