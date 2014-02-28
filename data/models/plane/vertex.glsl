#version 410

// Données attributes
// Position
in vec3 position;
// Coordonnées textures
in vec2 tex_coord;
// Normales
// in vec3 normal;

// Coordonnées injectée au shader tess_control
out vec2 texCoordV;
// out vec3 fnormalV;
out vec3 positionV;

void main()
{
	// Envoi de la position
    positionV = position;
    // Envoie de la coordonnée de texture
    texCoordV = tex_coord;
    // Envoi de la normale
    // fnormalV = normal;
}
