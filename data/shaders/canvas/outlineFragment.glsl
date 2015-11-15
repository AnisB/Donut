#version 410 

out vec4 frag_color;
uniform sampler2D canvas;
uniform sampler2D diff;
uniform sampler2D depth;
uniform int width;
uniform int lenght;

in vec2 texCoord;
#define MIN_STEP 0.0005
#define LINE_SIZE 2.0
const float blurSize = 1.0/512.0;

vec4 blurr(vec2 texPos)
{
   vec4 sum = vec4(0.0);
 
	sum += texture(diff, vec2(texCoord.x - 4.0*blurSize, texCoord.y)) * 0.05;
	sum += texture(diff, vec2(texCoord.x - 3.0*blurSize, texCoord.y)) * 0.09;
	sum += texture(diff, vec2(texCoord.x - 2.0*blurSize, texCoord.y)) * 0.12;
	sum += texture(diff, vec2(texCoord.x - blurSize, texCoord.y)) * 0.15;
	sum += texture(diff, vec2(texCoord.x, texCoord.y)) * 0.16;
	sum += texture(diff, vec2(texCoord.x + blurSize, texCoord.y)) * 0.15;
	sum += texture(diff, vec2(texCoord.x + 2.0*blurSize, texCoord.y)) * 0.12;
	sum += texture(diff, vec2(texCoord.x + 3.0*blurSize, texCoord.y)) * 0.09;
	sum += texture(diff, vec2(texCoord.x + 4.0*blurSize, texCoord.y)) * 0.05;
	return sum;
}
float outline(vec2 texPos)
{
	float filtre = 0;
	float center = texture(depth, texCoord).r;
	float left = texture(depth, vec2(texCoord.x+LINE_SIZE/width,texCoord.y)).r;
	float right = texture(depth, vec2(texCoord.x-LINE_SIZE/width,texCoord.y)).r;
	float up = texture(depth, vec2(texCoord.x,texCoord.y+LINE_SIZE/lenght)).r;
	float down = texture(depth, vec2(texCoord.x,texCoord.y+LINE_SIZE/lenght)).r;

	float gpx = (left-center)/2;
	float gnx = (right-center)/2;
	float gpy = (up-center)/2;
	float gny = (down-center)/2;
	if(abs(gpx)>MIN_STEP)
		filtre=1.0;
	if(abs(gnx)>MIN_STEP)
		filtre=1.0;
	if(abs(gpy)>MIN_STEP)
		filtre=1.0;		
	if(abs(gny)>MIN_STEP)
		filtre=1.0;	
	return filtre;
}
void main()
{
	frag_color = vec4(outline(texCoord))+blurr(texCoord)*texture(canvas, texCoord);
}
