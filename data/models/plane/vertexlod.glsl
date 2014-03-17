#version 410


uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection;

// Données attributes
// Coordonnées textures
in vec2 tex_coord;
in vec3 position;

// Coordonnées injectée au shader tess_control
out vec2 texCoordV;
out float dist;

void main()
{
    // Envoie de la coordonnée de texture
    texCoordV = tex_coord;
    // Envoie de la coordonnée de texture
    vec4 proj = projection*view*model*vec4(position,1.0);
    dist = proj.z;
}
