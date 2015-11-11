#version 410 

// Intput Data
in vec2 texCoord;

// Output data
out vec4 frag_color;

// Outputs to composite
uniform sampler2D deffered;
uniform sampler2D ssao_filtered;
uniform sampler2D ssao_prefiltered;
uniform sampler2D albedo;


void main()
{
    frag_color = texture(deffered, texCoord) * texture(ssao_filtered, texCoord);
}
