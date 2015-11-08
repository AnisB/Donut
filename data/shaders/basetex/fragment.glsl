#version 410

uniform sampler2D textureCmp;
uniform float fcoef;
out vec4 frag_color[4];

in vec2 texCoord;
in vec3 fnormal;
in vec4 ecPos;
in float flogz;


void main()
{
	gl_FragDepth = 0.5 * log2(flogz) * fcoef;
    frag_color[0]= texture(textureCmp,texCoord);
    frag_color[1] = vec4(gl_FrontFacing?fnormal:-fnormal,1.0);
    frag_color[2] = vec4(0.0,0.0,0.0,1.0);
    frag_color[3] = ecPos;
}
