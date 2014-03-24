#version 410


uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection;
uniform mat4 modelviewprojection;

// Données attributes
// Coordonnées textures
in vec2 tex_coord;
in vec3 position;
in vec3 normal;
// Coordonnées injectée au shader tess_control
out vec2 texCoordV;
out vec3 positionV;
out vec3 normalV;
out float dist;

void main()
{
    // Envoie de la coordonnée de texture
    texCoordV = tex_coord;
    positionV = position;
    normalV = normal;
    // Envoie de la coordonnée de texture
    vec4 proj = modelviewprojection*vec4(position,1.0);
    dist = proj.z;
}
