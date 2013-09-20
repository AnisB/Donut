

varying vec2 tex_coord;
void main()
{
	gl_FragColor = vec4(tex_coord.x,tex_coord.y, 1.0-tex_coord.x,1.0);
}