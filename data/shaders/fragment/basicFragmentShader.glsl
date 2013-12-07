#version 400

uniform sampler2D canvas;
uniform sampler2D depth;

in vec2 tex_coord;

void main()
{
	gl_FragColor = texture2D(canvas, tex_coord);
}