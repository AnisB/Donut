#version 410

uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection;
uniform mat4 modelviewprojection;

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;
// in vec3 positionTE[3];
// in vec3 fnormalTE[3];
in vec2 texCoordTE[3];
// in vec3 tePatchDistance[3];

// out vec3 gPatchDistance;
// out vec3 gTriDistance;

out vec2 texCoord;
out vec3 fnormal;

#define MAX_VAL 40.0

 vec3 unpack(vec3 parData)
{
    return (parData-vec3(0.5))*MAX_VAL;
}
uniform sampler2D displacement;
uniform sampler2D controlPoints;

// const int NB_UKNOTS = 3;
// #define EPSILON 0.0001
// const int uPow = 2;
// float uKnots[NB_UKNOTS] = float[];
// const int NB_VKNOTS = 3;
// uniform float vKnots[NB_VKNOTS];
// float derivatives[uPow+1];


vec3 getPoint(float parI, float parJ)
{
    return unpack(texture(controlPoints, vec2(parI, parJ)).rgb);
}

vec3 casteljau(float t, vec3 parPoints[5])
{
    vec3 Q[5];
    for(int i = 0; i<5; i++)
    {
        Q[i] = parPoints[i];
    }
    for(int k = 1; k < 5; k++)
    {
        for(int i = 0; i < 5-k; i++)
        {
            Q[i] = t*Q[i+1] + (1.0-t)*Q[i];
        }
    }
    return Q[0];
}
vec3 bezierSurface(vec2 parParam)
{
    vec3 points[5];
    for(int i = 0; i<5; ++i)
    {
        vec3 tmpPoints[5];
        for(int j = 0; j<5; ++j)
        {
            tmpPoints[j] = getPoint(i/5.0, j/5.0);
        }
        points[i] = casteljau(parParam.y,tmpPoints);
    }
    return casteljau(parParam.x,points);
}
vec3 pointPositions[3];
vec3 normal;

void main()
{
    for(int i=0; i<3; i++)
    {
        pointPositions[i] = bezierSurface(texCoordTE[i]);
    }
    normal = normalize(cross(pointPositions[1]-pointPositions[0],pointPositions[2]-pointPositions[0]));
    for(int i=0; i<3; i++)
    {
        texCoord = texCoordTE[i];
        gl_Position = projection * view * model * vec4(pointPositions[i], 1.0);
        fnormal = normal;
        EmitVertex();
    }
    // EndPrimitive();
}
