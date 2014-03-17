#version 410

// Données attributes
// Coordonnées textures
in vec2 tex_coord;

// Coordonnées injectée au shader tess_control
out vec2 texCoordV;

void main()
{
    // Envoi de la coordonnée de texture
    texCoordV = tex_coord;
}
