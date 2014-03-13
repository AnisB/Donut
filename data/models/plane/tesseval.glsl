#version 410

layout(triangles, equal_spacing, cw) in;


// Données récupérées
in vec3 positionTC[];
in vec2 texCoordTC[];
// in vec3 formalTC[];

// Données renvoyées au shader de geometrie
// out vec3 fnormalTE;
out vec2 texCoordTE;

// out vec3 tePatchDistance;

vec3 newPosition;
 
#define MAX_VAL 40.0

 vec3 unpack(vec3 parData)
{
  return (parData-vec3(0.5))*MAX_VAL;
}
void interpolate()
{
    // Calcul des données pour le geometry shader
  vec3 p0 = gl_TessCoord.x * positionTC[0];
  vec3 p1 = gl_TessCoord.y * positionTC[1];
  vec3 p2 = gl_TessCoord.z * positionTC[2];

  // vec3 n0 = gl_TessCoord.x * formalTC[0];
  // vec3 n1 = gl_TessCoord.y * formalTC[1];
  // vec3 n2 = gl_TessCoord.z * formalTC[2];

  vec2 tx0 = gl_TessCoord.x * texCoordTC[0];
  vec2 tx1 = gl_TessCoord.y * texCoordTC[1];
  vec2 tx2 = gl_TessCoord.z * texCoordTC[2];
  // tePatchDistance = gl_TessCoord;

  // positionTE = normalize(p0 + p1 + p2);
  // fnormalTE = normalize(n0 + n1 + n2);
  texCoordTE = (tx0 + tx1 + tx2);
  newPosition = (p0 + p1 + p2); 
}
void main()
{
  interpolate();
}
