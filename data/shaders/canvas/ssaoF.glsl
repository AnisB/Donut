#version 410 

out vec4 frag_color;
uniform sampler2D canvas;
uniform sampler2D depth;
uniform sampler2D nbuffer;
uniform sampler2D specbuffer;
uniform sampler2D posbuffer;
uniform int width;
uniform int lenght;

in vec2 texCoord;

void main()
{
	frag_color = texture(nbuffer, texCoord);
}
