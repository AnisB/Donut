#version 410 

// Input data
in vec2 texCoord;
// Out data
out vec4 frag_color;

// Input data
uniform sampler2D ssao_prefiltered;

uniform int uBlurSize = 4; // use size of noise texture

void main() 
{
  // Settings
  vec2 texelSize = 1.0 / vec2(textureSize(ssao_prefiltered, 0));
  frag_color = vec4(0.0);
  vec2 hlim = vec2(float(-uBlurSize) * 0.5 + 0.5);

  // Computing the kernel contibutions
  for (int x = 0; x < uBlurSize; ++x) 
  {
    for (int y = 0; y < uBlurSize; ++y) 
    {
      vec2 offset = vec2(float(x), float(y));
      offset += hlim;
      offset *= texelSize;
      frag_color += texture(ssao_prefiltered, texCoord + offset);
    }
  }
  frag_color = frag_color / (uBlurSize * uBlurSize);
}