#version 410

// Données attributes
// Coordonnées textures
in vec2 tex_coord;
in vec3 position;
in vec3 normal;

// Coordonnées injectée au shader tess_control
out vec2 texCoordV;
out vec3 positionV;
out vec3 normalV;

void main()
{
    // Envoi de la coordonnée de texture
    texCoordV = tex_coord;
    positionV = position;
    normalV = normal;
}
