#version 410 

out vec4 frag_color;

uniform sampler2D canvas;
uniform sampler2D depth;
uniform sampler2D nbuffer;
uniform sampler2D specbuffer;
uniform int width;
uniform int lenght;

in vec2 texCoord;

void main()
{
	if(texCoord.x<0.5)
	{
		if(texCoord.y<0.5)
		{
			frag_color = texture(canvas,texCoord);
		}
		else
		{
			frag_color = texture(nbuffer,vec2(texCoord.x,texCoord.y-0.5));
		}
	}
	else
	{
		if(texCoord.y<0.5)
		{
			frag_color = vec4(1.0-texture(depth,vec2(texCoord.x-0.5,texCoord.y)).r);
		}
		else
		{
			frag_color = texture(specbuffer,vec2(texCoord.x-0.5,texCoord.y-0.5));
		}
	}
}
