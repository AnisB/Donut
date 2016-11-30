#version 410 

// Input data
in vec2 texCoord;

// Out data
out vec4 frag_color;

// Input uniforms
uniform sampler2D composed;
uniform sampler2D specular;
uniform sampler2D reflection_smoothH;

void main()
{ 
	// Fetch reflection percentage
    float reflection = texture(specular, texCoord).z;

    // Fetch the original color of the pixel
    vec4 originalColor = texture(composed, texCoord.xy);

    // Fetch the original color of the pixel
    vec4 smoothedReflection = texture(reflection_smoothH, texCoord.xy);

	// return the target color
	frag_color = reflection * smoothedReflection +  (1-reflection) *originalColor;
}
