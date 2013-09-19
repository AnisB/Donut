
uniform sampler2D canvas;
uniform sampler2D depth;

varying vec2 tex_coord;


float sinusoid()
{
	return (abs(sin(tex_coord.x*100.0))*abs(cos(tex_coord.y*50.0)));
}

void main()
{
	vec4 color = texture2D(canvas, tex_coord);
	gl_FragColor = color*sinusoid();
}