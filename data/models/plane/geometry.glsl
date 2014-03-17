#version 410



layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

// Variable uniformes de model et camera
uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection;

// Variable d'entrée
in vec2 texCoordTE[3];

// Position du point courant
vec3 pointPositions[3];
// Normale de la primitive courante
vec3 normal;

// Rafinement de la grille
const int rafinement = 5;

// Paramètres de sortie
out vec2 texCoord;
out vec3 fnormal;

#define MAX_VAL 40.0

// Texture de deplacement
uniform sampler2D displacement;
// texture de point de controle
uniform sampler2D controlPoints;

// Depaquetage des données
vec3 unpack(vec3 parData)
{
    return (parData-vec3(0.5))*MAX_VAL;
}

// Récupération d'un point de controle par i,j
vec3 getPoint(float parI, float parJ)
{
    return unpack(texture(controlPoints, vec2(parI, parJ)).rgb);
}

// Algorithme de casteljau pour une courbe parPoints à t
vec3 casteljau(float t, vec3 parPoints[rafinement])
{
    vec3 Q[rafinement];
    for(int i = 0; i<rafinement; i++)
    {
        Q[i] = parPoints[i];
    }
    for(int k = 1; k < rafinement; k++)
    {
        for(int i = 0; i < rafinement-k; i++)
        {
            Q[i] = t*Q[i+1] + (1.0-t)*Q[i];
        }
    }
    return Q[0];
}

// Calcul d'un point sur la surface de bezier à (parPara.x, parParam.y)
vec3 bezierSurface(vec2 parParam)
{
    vec3 points[rafinement];
    for(int i = 0; i<rafinement; ++i)
    {
        vec3 tmpPoints[rafinement];
        for(int j = 0; j<rafinement; ++j)
        {
            tmpPoints[j] = getPoint(i/float(rafinement), j/float(rafinement));
        }
        points[i] = casteljau(parParam.y,tmpPoints);
    }
    return casteljau(parParam.x,points);
}


void main()
{
    // Pour chacun des points du triangle
    for(int i=0; i<3; i++)
    {
        // On calcule le point de la surface
        pointPositions[i] = bezierSurface(texCoordTE[i]);
    }
    // On calcule la normale de la surface
    normal = normalize(cross(pointPositions[1]-pointPositions[0],
                    pointPositions[2]-pointPositions[0]));
    // On ganère les vertex associés
    for(int i=0; i<3; i++)
    {
        texCoord = texCoordTE[i];
        gl_Position = projection * view * model 
                    * vec4(pointPositions[i], 1.0);
        fnormal = normal;
        EmitVertex();
    }
    EndPrimitive();
}