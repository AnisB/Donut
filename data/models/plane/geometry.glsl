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
in vec3 tePatchDistance[3];

out vec3 gPatchDistance;
out vec3 gTriDistance;

out vec2 texCoord;
// out vec3 fnormal;
 
void main()
{
    // vec3 A = positionTE[2] - positionTE[0];
    // vec3 B = positionTE[1] - positionTE[0];
    //  gFacetNormal = NormalMatrix * normalize(cross(A, B));

    gPatchDistance = tePatchDistance[0];
    gTriDistance = vec3(1, 0, 0);
    texCoord = texCoordTE[0];
    // fnormal = fnormalTE[0];
    gl_Position = gl_in[0].gl_Position; EmitVertex();
 
    gPatchDistance = tePatchDistance[1];
    gTriDistance = vec3(0, 1, 0);
    texCoord = texCoordTE[1];
    // fnormal = fnormalTE[1];
    gl_Position = gl_in[1].gl_Position; EmitVertex();
 
    gPatchDistance = tePatchDistance[2];
    gTriDistance = vec3(0, 0, 1);
    texCoord = texCoordTE[2];
    // fnormal = fnormalTE[2];
    gl_Position = gl_in[2].gl_Position; EmitVertex();
    EndPrimitive();
}
