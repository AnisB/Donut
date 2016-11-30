#version 410 

// Input data
in vec2 texCoord;

// Out data
out vec4 frag_color;

// Input uniforms
uniform sampler2D reflection;

uniform int width;
uniform int lenght;
uniform float focus;

const ivec2 offsets[7] = ivec2[](ivec2(0, -3), ivec2(0, -2), ivec2(0, -1), ivec2(0, 0), ivec2(0, 1), 
      ivec2(0, 2), ivec2(0, 3));
const float weights[7] = float[](0.001f, 0.028f, 0.233f, 0.474f, 0.233f, 0.028f, 0.001f);
 
void main()
{
  // Final color
  vec4 color = vec4(0.0, 0.0, 0.0, 1.0);

  // Compute the blurr
  for(uint i = 0; i < 7; ++i)
  {
    color += texture(reflection, vec2(texCoord + vec2(offsets[i].x/1280.0, offsets[i].y/720.0))) * weights[i];
  }

  // return the color
  frag_color = color;
}

