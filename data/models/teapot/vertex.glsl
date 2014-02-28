#version 410

uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection;
uniform mat4 modelviewprojection;

in vec3 position;
in vec3 normal;
in vec2 tex_coord;

out vec3 fnormalV;
out vec2 txCoordV;
out vec4 ecPosV;

vec3 packVec3(vec3 parVec3)
{
    return (parVec3*0.5+vec3(0.5));
}

vec4 packVec4(vec4 parVec4)
{
    return (parVec4*0.5+vec4(0.5, 0.5, 0.5,0.0));

}

void main()
{
    gl_Position = modelviewprojection*vec4(position,1.0);
    txCoordV = tex_coord;
    fnormalV = packVec3((vec4(normal,0.0)*inverse(view*model)).xyz);
    ecPosV = view*model*vec4(position,1.0);
    float norm = length(ecPosV);
    ecPosV/=norm;
    ecPosV.w = 1.0/norm;
    ecPosV = packVec4(ecPosV);
}
