#version 400

out vec2 tex_coord;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;	
	tex_coord = vec2((gl_Position.x+1.0)*0.5,(gl_Position.y+1.0)*0.5);
	gl_TexCoord[0] = gl_MultiTexCoord0;
}