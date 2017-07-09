#version 410

layout(triangles, equal_spacing, cw) in;

uniform mat4 model;
uniform mat4 modelviewprojection;


uniform sampler2D textureCmp;
// Données récupérées
in vec2 texCoordTC[];
in vec3 positionTC[];
in vec3 normalTC[];

// Données renvoyées au shader de geometrie
out vec2 txCoordTE;
out vec3 fnormalTE;
vec3 position;
#define MAX_VAL 40.0

void interpolate()
{
  // Calcul des données pour le geometry shader
  vec2 tx0 = gl_TessCoord.x * texCoordTC[0];
  vec2 tx1 = gl_TessCoord.y * texCoordTC[1];
  vec2 tx2 = gl_TessCoord.z * texCoordTC[2];

  vec3 p0 = gl_TessCoord.x * positionTC[0];
  vec3 p1 = gl_TessCoord.y * positionTC[1];
  vec3 p2 = gl_TessCoord.z * positionTC[2];

  vec3 n0 = gl_TessCoord.x * normalTC[0];
  vec3 n1 = gl_TessCoord.y * normalTC[1];
  vec3 n2 = gl_TessCoord.z * normalTC[2];

  txCoordTE = (tx0 + tx1 + tx2);
  position = (p0 + p1 + p2);
  fnormalTE = (model*vec4(n0 + n1 + n2,0.0)).xyz;
}

void main()
{
  interpolate();
  gl_Position = modelviewprojection*vec4(position-texture(textureCmp,vec2((txCoordTE.x+2.0)/6.0,txCoordTE.y)).r*0.1*fnormalTE,1.0);
}
