#version 410 

// Input data
in vec2 texCoord;

// Output data
out vec4 frag_color;

// Useful consts
const float sample_radius = 0.1f;
const vec2 dirs[8] = vec2[](vec2(1,0),vec2(-1,0), vec2(0,1),vec2(0,-1), vec2(0.70710678118, 0.70710678118), vec2(-0.70710678118, 0.70710678118), vec2(-0.70710678118, -0.70710678118), vec2(0.70710678118, -0.70710678118));
const float randomShift = 16.0;
const int nbIterations = 8;
const float scale = 0.1;

// Uniform data
uniform sampler2D albedo;
uniform sampler2D normal;
uniform sampler2D specular;
uniform sampler2D position;
uniform sampler2D depth;
uniform sampler2D random;
uniform int width;
uniform int lenght;

float doAmbientOcclusion(vec2 tcoord, vec2 uv, vec3 p, vec3 cnorm)
{
  vec3 diff = texture(position, tcoord + uv).xyz - p;
  float lengthDiff = length(diff);
  vec3 v = diff/ lengthDiff;
  float d = lengthDiff * scale;
  return max(0.0,dot(cnorm,v)-0.1)*(1.0/(1.0+d));
}

void main()
{
  // If its too far, just forget about it
  // Maybe should not be done?
  float d = texture(depth, texCoord).r;
  vec4 p4 = texture(position, texCoord);

  vec3 p = p4.xyz;
  // Fetching the data
  vec3 n = texture(normal, texCoord).xyz;
  vec2 rand = texture(random, texCoord * randomShift).xy;

  // We get the radius value
  float ao = 0.0f;
  float rad = sample_radius/p.z;

  // For each iteration
  for (int j = 0; j < nbIterations; ++j)
  {
    // We fetch the 2 coord to  check
    vec2 coord1 = reflect(dirs[j], rand) * rad;
    vec2 coord2 = vec2(coord1.x*0.707 - coord1.y*0.707, coord1.x*0.707 + coord1.y*0.707);
    
    ao += doAmbientOcclusion(texCoord,coord1*0.25, p, n);
    ao += doAmbientOcclusion(texCoord,coord2*0.5, p, n);
    ao += doAmbientOcclusion(texCoord,coord1*0.75, p, n);
    ao += doAmbientOcclusion(texCoord,coord2, p, n);
  }
  ao = ao / nbIterations;
  ao = 1.0 - ao;
  frag_color = p4.w == 1.0f ? vec4(ao,ao,ao,1.0) : vec4(1.0);
}