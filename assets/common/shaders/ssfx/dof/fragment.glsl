#version 410 

// Input data
in vec2 texCoord;

// Out data
out vec4 frag_color;

// Input uniforms
uniform sampler2D dof_input;
uniform sampler2D depth;

uniform float near_plane;
uniform float far_plane;
uniform float focus;

// Values
#define MIN_STEP 0.005
#define LINE_SIZE 2.0
// Blur size
const float blurSize = 1.0/1024.0;

float linear_depth()
{
  float depthV =  texture(depth, texCoord).r;
  depthV = 2.0 * depthV - 1.0;
  float zLinear = 2.0 * near_plane * far_plane / (far_plane + near_plane - depthV * (far_plane - near_plane));
  return zLinear;
}

float blur_intensity()
{
  float depthV =  linear_depth();
  return focus - depthV > 0.0 ? pow((focus - depthV)/focus, 0.8) : clamp((depthV - focus)/(3.0*focus), 0.0,1.0);
}

// Blur function
vec4 blurr(vec2 texPos)
{
  vec4 sum = vec4(0.0);
  float intensity = blur_intensity();
  sum += texture(dof_input, vec2(texCoord.x - 4.0*blurSize*intensity, texCoord.y)) * 0.05;
  sum += texture(dof_input, vec2(texCoord.x - 3.0*blurSize*intensity, texCoord.y)) * 0.09;
  sum += texture(dof_input, vec2(texCoord.x - 2.0*blurSize*intensity, texCoord.y)) * 0.12;
  sum += texture(dof_input, vec2(texCoord.x - blurSize*intensity, texCoord.y)) * 0.15;
  sum += texture(dof_input, vec2(texCoord.x, texCoord.y)) * 0.16;
  sum += texture(dof_input, vec2(texCoord.x + blurSize*intensity, texCoord.y)) * 0.15;
  sum += texture(dof_input, vec2(texCoord.x + 2.0*blurSize*intensity, texCoord.y)) * 0.12;
  sum += texture(dof_input, vec2(texCoord.x + 3.0*blurSize*intensity, texCoord.y)) * 0.09;
  sum += texture(dof_input, vec2(texCoord.x + 4.0*blurSize*intensity, texCoord.y)) * 0.05;
  return sum;
}

void main()
{ 
    frag_color = blurr(texCoord);
}
