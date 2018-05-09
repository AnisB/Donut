#version 410 

// Setting output data
layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

// Input data
in vec2 texCoordV[];
in vec3 fnormalV[];
in vec4 ecPosV[];
in float flogzG[];

// Output Data
out vec2 texCoord;
out vec3 fnormal;
out vec4 ecPos;

void main()
{ 
  for(int i=0; i<3; i++)
  {
    // Transfer to fragment
    gl_Position = gl_in[i].gl_Position;
    texCoord = texCoordV[i];
    fnormal = fnormalV[i];
    ecPos = ecPosV[i];
    // Emit vertex
    EmitVertex();
  }
  // End of primitive
  EndPrimitive();
}  