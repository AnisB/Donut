#version 410 

// Input data
in vec2 texCoord;

// Out data
out vec4 frag_color;

// Input uniforms
uniform sampler2D final;
uniform sampler2D depth;

uniform int width;
uniform int lenght;
uniform float focus;

// Values
#define MIN_STEP 0.005
#define LINE_SIZE 2.0
// Blur size
const float blurSize = 1.0/1024.0;

// Blur function
vec4 blurr(vec2 texPos)
{
  vec4 sum = vec4(0.0);
  float depthV =  texture(depth, texCoord).r;
  float intensity = abs(depthV-0.6)*2.0;
  sum += texture(final, vec2(texCoord.x - 4.0*blurSize*intensity, texCoord.y)) * 0.05;
  sum += texture(final, vec2(texCoord.x - 3.0*blurSize*intensity, texCoord.y)) * 0.09;
  sum += texture(final, vec2(texCoord.x - 2.0*blurSize*intensity, texCoord.y)) * 0.12;
  sum += texture(final, vec2(texCoord.x - blurSize*intensity, texCoord.y)) * 0.15;
  sum += texture(final, vec2(texCoord.x, texCoord.y)) * 0.16;
  sum += texture(final, vec2(texCoord.x + blurSize*intensity, texCoord.y)) * 0.15;
  sum += texture(final, vec2(texCoord.x + 2.0*blurSize*intensity, texCoord.y)) * 0.12;
  sum += texture(final, vec2(texCoord.x + 3.0*blurSize*intensity, texCoord.y)) * 0.09;
  sum += texture(final, vec2(texCoord.x + 4.0*blurSize*intensity, texCoord.y)) * 0.05;
  return sum;
}

void main()
{ 
    frag_color = blurr(texCoord);
}
