#version 330 
layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

in vec3 fnormalV[];
in vec2 txCoordV[];
in vec4 ecPosV[];

out vec2 txCoordG;
out vec3 fnormalG;
out vec4 ecPosG;

void main()
{ 
  for(int i=0; i<3; i++)
  {
    gl_Position = gl_in[i].gl_Position;
    txCoordG = txCoordV[i];
    fnormalG = fnormalV[i];
    ecPosG = ecPosV[i];
    EmitVertex();
  }
  EndPrimitive();
}  