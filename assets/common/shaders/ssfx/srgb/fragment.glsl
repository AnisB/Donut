#version 410 

// Input data
in vec2 texCoord;

// Out data
out vec4 frag_color;

// Input uniforms
uniform sampler2D srgb_input;

float to_srgb(float value)
{
  return (value <= 0.0031308) ? 12.92 * value :(1.0 + 0.055) * pow(value, 1.0 / 2.4) - 0.055;
}

vec4 col_to_srgb(vec4 col)
{
  return vec4(to_srgb(col.x), to_srgb(col.y), to_srgb(col.z), col.w);
}

void main()
{ 
    frag_color = col_to_srgb(texture(srgb_input, texCoord));
}
