#version 410 

// Input data
in vec2 texCoord;
// Out data
out vec4 frag_color;

// Input data
uniform sampler2D rendered;
uniform sampler2D depth;

// Input uniforms
uniform int width;
uniform int lenght;

// Values
#define MIN_STEP 0.005
#define LINE_SIZE 2.0
// Blur size
const float blurSize = 1.0/512.0;

// Blur function
vec4 blurr(vec2 texPos)
{
  vec4 sum = vec4(0.0);
  float depthV =  texture(depth, texCoord).r/2.0;
  sum += texture(rendered, vec2(texCoord.x - 4.0*blurSize*depthV, texCoord.y)) * 0.05;
  sum += texture(rendered, vec2(texCoord.x - 3.0*blurSize*depthV, texCoord.y)) * 0.09;
  sum += texture(rendered, vec2(texCoord.x - 2.0*blurSize*depthV, texCoord.y)) * 0.12;
  sum += texture(rendered, vec2(texCoord.x - blurSize*depthV, texCoord.y)) * 0.15;
  sum += texture(rendered, vec2(texCoord.x, texCoord.y)) * 0.16;
  sum += texture(rendered, vec2(texCoord.x + blurSize*depthV, texCoord.y)) * 0.15;
  sum += texture(rendered, vec2(texCoord.x + 2.0*blurSize*depthV, texCoord.y)) * 0.12;
  sum += texture(rendered, vec2(texCoord.x + 3.0*blurSize*depthV, texCoord.y)) * 0.09;
  sum += texture(rendered, vec2(texCoord.x + 4.0*blurSize*depthV, texCoord.y)) * 0.05;
  return sum;
}

void main()
{ 
    frag_color =  blurr(texCoord);
}
