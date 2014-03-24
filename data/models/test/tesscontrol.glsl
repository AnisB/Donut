#version 410

layout(vertices = 3) out;

// Données recues du vertex shader
in vec2 texCoordV[];
in vec3 positionV[];
in vec3 normalV[];


// Données transférées au tess_eval shader
out vec2 texCoordTC[];
out vec3 positionTC[];
out vec3 normalTC[];

// Niveau de raffinement
uniform float TessLevelInner;
uniform float TessLevelOuter;
 
#define ID gl_InvocationID
void main()
{
    // Copie des données pour envoi au tess_eval
    texCoordTC[ID] = texCoordV[ID];
    positionTC[ID] = positionV[ID];
    normalTC[ID] = normalV[ID];

    // Definition du rafinement
    if (ID == 0) 
    {
        gl_TessLevelInner[0] = TessLevelInner;
        gl_TessLevelOuter[0] = TessLevelOuter;
        gl_TessLevelOuter[1] = TessLevelOuter;
        gl_TessLevelOuter[2] = TessLevelOuter;
    }
}
