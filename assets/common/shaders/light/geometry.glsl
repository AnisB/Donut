#version 410 

// This is a gbuffer light vertex pipeline

// Primitives type
layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

// Intput Data
in vec2 texCoordV[];

// Output Data
out vec2 texCoord;

void main()
{ 
	// Just emit the vertices
	for(int i=0; i<3; i++)
	{
		gl_Position = gl_in[i].gl_Position;
		texCoord = texCoordV[i];
		EmitVertex();
	}
	EndPrimitive();
}  