#version 410

uniform sampler2D diffMap;
out vec4 fragColor;
// in vec3 gFacetNormal;
in vec3 gTriDistance;
in vec3 gPatchDistance;
in float gPrimitive;


in vec2 texCoord;
// in vec3 fnormal;
 
float amplify(float d, float scale, float offset)
{
    d = scale * d + offset;
    d = clamp(d, 0, 1);
    d = 1 - exp2(-2*d*d);
    return d;
}
 
void main()
{
    // vec3 N = normalize(gFacetNormal);
    // vec3 L = LightPosition;
    // float df = abs(dot(N, L));
    // vec3 color = AmbientMaterial + df * DiffuseMaterial;
 
    float d1 = min(min(gTriDistance.x, gTriDistance.y), gTriDistance.z);
    float d2 = min(min(gPatchDistance.x, gPatchDistance.y), gPatchDistance.z);
    vec3 color = amplify(d1, 40, -0.5) * amplify(d2, 60, -0.5) * vec3(1.0,0.0,0.0);
 
    fragColor = texture(diffMap, texCoord);
}
