#version 410

layout(triangles, equal_spacing, cw) in;


// Données récupérées
in vec2 texCoordTC[];

// Données renvoyées au shader de geometrie
out vec2 texCoordTE;

#define MAX_VAL 40.0

void interpolate()
{
  // Calcul des données pour le geometry shader
  vec2 tx0 = gl_TessCoord.x * texCoordTC[0];
  vec2 tx1 = gl_TessCoord.y * texCoordTC[1];
  vec2 tx2 = gl_TessCoord.z * texCoordTC[2];

  texCoordTE = (tx0 + tx1 + tx2);
}

void main()
{
  interpolate();
}
