#version 410 

// Input data
in vec2 texCoord;

// Output data
out vec4 frag_color;

// Useful consts
const float sample_radius = 2.0;
const vec2 dirs[4] = vec2[](vec2(1,0),vec2(-1,0), vec2(0,1),vec2(0,-1));
const float randomShift = 8.0;
const int nbIterations = 4;
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
  vec3 v = normalize(diff);
  float d = length(diff)*scale;
  return max(0.0,dot(cnorm,v)-0.1)*(1.0/(1.0+d));
}

void main()
{
  // If its too far, just forget about it
  // Maybe should not be done?
  float d = texture(depth, texCoord).r;
  if(d == 1.0)
  {
    frag_color = vec4(1.0);
    return;
  }

  // Fetching the data
  vec3 p = texture(position, texCoord).xyz;
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
  frag_color = vec4(ao,ao,ao,1.0);
}