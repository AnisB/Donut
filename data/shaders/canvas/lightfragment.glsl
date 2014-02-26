#version 410 

out vec4 frag_color;
uniform sampler2D canvas;
uniform sampler2D diff;
uniform sampler2D depth;

in vec2 texCoord;

void main()
{
	//float dep = 1-texture(depth, texCoord).r;
    //frag_color = vec4(dep,dep,dep,1.0);
    frag_color = texture(canvas, texCoord)*texture(diff, texCoord);
}
