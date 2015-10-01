#version 410

uniform sampler2D diffMap;
uniform sampler2D controlPoints;

out vec4 fragColor;
in float gPrimitive;

in vec2 texCoord;
in vec3 fnormal;

uniform mat4 model; 

void main()
{
    if(gl_FrontFacing)
        fragColor = vec4(texture(diffMap, texCoord).rgb*dot(fnormal,normalize((inverse(model)*vec4(0.0,0.0,1.0,1.0)).xyz)),1.0);
    else
        fragColor = vec4(texture(diffMap, texCoord).rgb*-dot(fnormal,normalize((inverse(model)*vec4(0.0,0.0,1.0,1.0)).xyz)),1.0);
}