#version 410 

// input data
in vec2 texCoord;
// output data
out vec4 frag_color;

// Uniform data
uniform sampler2D world_normal;
uniform sampler2D world_position;
uniform vec3 camera_position;

// SH data
uniform float redCoeff[9];
uniform float greenCoeff[9];
uniform float blueCoeff[9];
const float c1 = 0.429043;
const float c2 = 0.511664;
const float c3 = 0.743125;
const float c4 = 0.886227;
const float c5 = 0.247708;


// Clacul de l'eclairage à un point donné
float computeEVal(vec3 worldSpaceNormal, float parCoeff[9])
{
    float x = worldSpaceNormal.x;
    float y = worldSpaceNormal.y;
    float z = worldSpaceNormal.z;
    float x2 = worldSpaceNormal.x*worldSpaceNormal.x;
    float y2 = worldSpaceNormal.y*worldSpaceNormal.y;
    float z2 = worldSpaceNormal.z*worldSpaceNormal.z;
    return (c1*parCoeff[8]*(x2-y2)+c3*parCoeff[6]*z2+c4*parCoeff[0]-c5*parCoeff[6]
            +2.0*c1*(parCoeff[4]*x*y+parCoeff[7]*x*z+parCoeff[5]*y*z)
            +2.0*c2*(parCoeff[3]*x+parCoeff[1]*y+parCoeff[2]*z));
}

void main(void) 
{
    vec3 ws_normal = texture(world_normal, texCoord).xyz;
    vec3 ws_position = texture(world_position, texCoord).xyz;
    vec3 refl_dir = reflect(normalize(ws_position - camera_position), ws_normal);
    float Ered = computeEVal(refl_dir, redCoeff);
    float Egreen = computeEVal(refl_dir, greenCoeff);
    float Eblue = computeEVal(refl_dir, blueCoeff);
    // Calcul de la lumière
    frag_color = vec4(Ered,Egreen,Eblue, 1.0);
}