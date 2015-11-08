#version 410 

out vec4 frag_color;
uniform sampler2D canvas;
uniform sampler2D depth;
uniform sampler2D nbuffer;
uniform sampler2D specbuffer;
uniform sampler2D posbuffer;
uniform sampler2D random;
uniform int width;
uniform int lenght;

in vec2 texCoord;
#define MIN_STEP 0.005
#define LINE_SIZE 2.0
const float blurSize = 1.0/512.0;

vec4 blurr(vec2 texPos)
{
  vec4 sum = vec4(0.0);
  float depthV =  texture(depth, texCoord).r;
  depthV = pow(depthV, 2.0);
  sum += texture(canvas, vec2(texCoord.x - 4.0*blurSize*depthV, texCoord.y)) * 0.05;
  sum += texture(canvas, vec2(texCoord.x - 3.0*blurSize*depthV, texCoord.y)) * 0.09;
  sum += texture(canvas, vec2(texCoord.x - 2.0*blurSize*depthV, texCoord.y)) * 0.12;
  sum += texture(canvas, vec2(texCoord.x - blurSize*depthV, texCoord.y)) * 0.15;
  sum += texture(canvas, vec2(texCoord.x, texCoord.y)) * 0.16;
  sum += texture(canvas, vec2(texCoord.x + blurSize*depthV, texCoord.y)) * 0.15;
  sum += texture(canvas, vec2(texCoord.x + 2.0*blurSize*depthV, texCoord.y)) * 0.12;
  sum += texture(canvas, vec2(texCoord.x + 3.0*blurSize*depthV, texCoord.y)) * 0.09;
  sum += texture(canvas, vec2(texCoord.x + 4.0*blurSize*depthV, texCoord.y)) * 0.05;
  return sum;
}

void main()
{ 
    frag_color =  blurr(texCoord);
}
