#version 410

uniform sampler2D diffMap;

out vec4 fragColor;
in float gPrimitive;

in vec2 texCoord;
in vec3 fnormal;

void main()
{
        fragColor = vec4(texture(diffMap, texCoord).rgb*fnormal,1.0);
}
