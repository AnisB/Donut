#version 410 

in vec2 txCoord;
in vec3 fnormal;

uniform sampler2D textureCmp;

out vec4 frag_color;

// Les couleurs injevtées
uniform float redCoeff[9];
uniform float greenCoeff[9];
uniform float blueCoeff[9];
// Coefficient constants
const float c1 = 0.429043;
const float c2 = 0.511664;
const float c3 = 0.743125;
const float c4 = 0.886227;
const float c5 = 0.247708;


// Clacul de l'eclairage à un point donné
float computeEVal(float parCoeff[9])
{
    float x = fnormal.x;
    float y = fnormal.y;
    float z = fnormal.z;
    float x2 = fnormal.x*fnormal.x;
    float y2 = fnormal.y*fnormal.y;
    float z2 = fnormal.z*fnormal.z;
    return (c1*parCoeff[8]*(x2-y2)+c3*parCoeff[6]*z2+c4*parCoeff[0]-c5*parCoeff[6]
            +2.0*c1*(parCoeff[4]*x*y+parCoeff[7]*x*z+parCoeff[5]*y*z)
            +2.0*c2*(parCoeff[3]*x+parCoeff[1]*y+parCoeff[2]*z));
}
void main(void) 
{
    float Ered = computeEVal(redCoeff);
    float Egreen = computeEVal(greenCoeff);
    float Eblue = computeEVal(blueCoeff);
    // Calcul de la lumière
    // frag_color = vec4(vec3(Ered,Egreen,Eblue)* texture(textureCmp,vec2((txCoord.x+2.0)/6.0,txCoord.y)).xyz,1.0);
    frag_color = vec4(vec3(Ered,Egreen,Eblue)*texture(textureCmp,vec2(txCoord.x/6.0,txCoord.y)).xyz,1.0);

}