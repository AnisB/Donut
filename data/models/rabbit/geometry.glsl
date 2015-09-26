#version 410 

uniform mat4 model; 
uniform mat4 view; 


layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

in vec3 ecPos[3];
out vec3 fnormalG;

void main()
{ 
  vec3 normal = normalize(cross(ecPos[1]-ecPos[0],ecPos[2]-ecPos[0]));
  normal = (vec4(normal,0.0)*inverse(view*model)).xyz;
  for(int i=0; i<3; i++)
  {
    gl_Position = gl_in[i].gl_Position;
    fnormalG = normal;
    EmitVertex();
  }
  EndPrimitive();
}  