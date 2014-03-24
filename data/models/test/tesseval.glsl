#version 410

layout(triangles, equal_spacing, cw) in;


uniform mat4 modelviewprojection;

// Données récupérées
in vec2 texCoordTC[];
in vec3 normalTC[];
in vec3 positionTC[];

// Données renvoyées au shader de geometrie
out vec2 texCoord;
out vec3 fnormal;
vec3 position;

void interpolate()
{
  // Calcul des données pour le geometry shader
  vec2 tx0 = gl_TessCoord.x * texCoordTC[0];
  vec2 tx1 = gl_TessCoord.y * texCoordTC[1];
  vec2 tx2 = gl_TessCoord.z * texCoordTC[2];

  texCoord = (tx0 + tx1 + tx2);

  // Calcul des données pour le geometry shader
  vec3 n0 = gl_TessCoord.x * normalTC[0];
  vec3 n1 = gl_TessCoord.y * normalTC[1];
  vec3 n2 = gl_TessCoord.z * normalTC[2];

  fnormal = (n0 + n1 + n2);

  // Calcul des données pour le geometry shader
  vec3 p0 = gl_TessCoord.x * positionTC[0];
  vec3 p1 = gl_TessCoord.y * positionTC[1];
  vec3 p2 = gl_TessCoord.z * positionTC[2];

  position = (p0 + p1 + p2);
}

void main()
{
  interpolate();
  gl_Position = modelviewprojection*vec4(position,1.0);
}
