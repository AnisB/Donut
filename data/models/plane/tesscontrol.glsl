#version 410

layout(vertices = 3) out;

// Données recues du vertex shader
in vec2 texCoordV[];
// in vec3 fnormalV[];
in vec3 positionV[];

// Données transférées au tess_eval shader
out vec3 positionTC[];
out vec2 texCoordTC[];
// out vec3 formalTC[];

// Niveau de raffinement
uniform float TessLevelInner;
uniform float TessLevelOuter;
 
#define ID gl_InvocationID
void main()
{
    // Copie des données pour envoi au tess_eval
    positionTC[ID] = positionV[ID].xyz;
    // formalTC[ID] = fnormalV[ID];
    texCoordTC[ID] = texCoordV[ID];

    // Definition du rafinement
    if (ID == 0) 
    {
        gl_TessLevelInner[0] = TessLevelInner;
        gl_TessLevelOuter[0] = TessLevelOuter;
        gl_TessLevelOuter[1] = TessLevelOuter;
        gl_TessLevelOuter[2] = TessLevelOuter;
    }
}
