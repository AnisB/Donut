#version 330 
layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

in vec2 texCoordV[];
in vec3 fnormalV[];
in vec4 ecPosV[];
in float flogzG[];

out vec2 texCoord;
out vec3 fnormal;
out vec4 ecPos;
out float flogz;

void main()
{ 
  for(int i=0; i<3; i++)
  {
    gl_Position = gl_in[i].gl_Position;
    texCoord = texCoordV[i];
    fnormal = fnormalV[i];
    ecPos = ecPosV[i];
    flogz = flogzG[i];
    EmitVertex();
  }
  EndPrimitive();
}  