#version 410

uniform sampler2D points;
out vec4 frag_color;

in vec2 texCoord;
in vec4 unitX;
in vec4 unitY;
in vec4 coinInfGauche;
in vec3 cameraPosition;

#define focalDistance 50.0f
const float hauteurEcran = 1.52638111*focalDistance;
const float ratio = 1280.0/720.0;

#define MAX_VAL 1000000.0
#define EPSILON 0.00001
uniform int nbTriangles;
struct TRay
{
	vec3 origin;
	vec3 direction;
};

struct TTriangle
{
	vec3 p0;
	vec3 n0;
	vec2 uv0;
	vec3 p1;
	vec3 n1;
	vec2 uv1;
	vec3 p2;
	vec3 n2;
	vec2 uv2;
};

struct TIntersection
{
	bool isValid;
	vec3 position;
	vec3 normal;
	vec2 uv;
	int prim;
	float distance;
};

vec3 unpack(vec3 parVector)
{
	return ((parVector-vec3(0.5)) * MAX_VAL);
}
vec2 unpack(vec2 parVector)
{
	return ((parVector-vec2(0.5)) * MAX_VAL);
}

TTriangle getTriangle(int parI)
{
	TTriangle parTriangle;
	float xVal = float(parI)/float(nbTriangles);
	parTriangle.p0 = unpack(texture(points, vec2(0.01,xVal)).xyz);
	parTriangle.n0 = unpack(texture(points, vec2(0.12,xVal)).xyz);
	parTriangle.uv0 = unpack(texture(points, vec2(0.23,xVal)).xy);

	parTriangle.p1 = unpack(texture(points, vec2(0.34,xVal)).xyz);
	parTriangle.n1 = unpack(texture(points, vec2(0.45,xVal)).xyz);
	parTriangle.uv1 = unpack(texture(points, vec2(0.56,xVal)).xy);

	parTriangle.p2 = unpack(texture(points, vec2(0.67,xVal)).xyz);
	parTriangle.n2 = unpack(texture(points, vec2(0.78,xVal)).xyz);
	parTriangle.uv2 = unpack(texture(points, vec2(0.89,xVal)).xy);
	return parTriangle;
}

TIntersection intersectWithTriangle(TRay parRay, TTriangle parTheTriangle)
{
    TIntersection intersect;
    intersect.isValid = false;
    intersect.position = vec3(0.0);
    intersect.normal = vec3(0.0);
    intersect.prim = 0;
    intersect.uv = vec2(0.0);

    vec3 edge1 = parTheTriangle.p1 - parTheTriangle.p0;
    vec3 edge2 = parTheTriangle.p2 - parTheTriangle.p0;
    vec3 vecP = cross(parRay.direction, edge2);
    float det = dot(edge1, vecP);

    if(abs(det)<EPSILON)
        return intersect;
    float invDet = 1.0f / det;
    vec3 vecS = parRay.origin - parTheTriangle.p0;
    float u = dot(vecS, vecP) * invDet;
    if(u<0 || u>1)
        return intersect;
    vec3 vecQ = cross(vecS, edge1);
    float v = dot(parRay.direction, vecQ) * invDet;
    if(v<0 || u + v > 1)
        return intersect;
    float distance = dot(edge2, vecQ) * invDet;
    vec3 I = parRay.origin + distance * parRay.direction ;
    if(distance > EPSILON)
        return intersect;
    distance = abs(distance);

    vec2 uvI = u*(parTheTriangle.uv1-parTheTriangle.uv0)+v*(parTheTriangle.uv2-parTheTriangle.uv0)+parTheTriangle.uv0;
    vec3 normal = u*(parTheTriangle.n1-parTheTriangle.n0)+v*(parTheTriangle.n2-parTheTriangle.n0)+parTheTriangle.n0;
    intersect.distance = distance;
    intersect.position = I;
    intersect.uv = uvI;
    if(dot(parRay.direction, normal) > 0)
        intersect.normal = -normal;
    else
        intersect.normal = normal;
    intersect.isValid = true;
    return intersect;
}
vec4 rayTrace(TRay parCamera)
{
	TIntersection finalIntersect;
	finalIntersect.distance = MAX_VAL;
	finalIntersect.isValid =false;
	for(int i = 0; i < nbTriangles; ++i)
	{
		TIntersection inter = intersectWithTriangle(parCamera,getTriangle(i));
		if(inter.isValid && inter.distance<finalIntersect.distance)
		{
			finalIntersect=inter;
		}
	}
	if(finalIntersect.isValid)
		return vec4(1.0,0.0,0.0,1.0);
	else
		return vec4(0.0,0.0,0.0,1.0);
}
vec4 rayTrace2(TRay parCamera)
{
	TTriangle tri;
	tri.p1 = vec3(0.0, 0.0, 10.0);
	tri.p0 = vec3(0.0, 1.0, 10.0);
	tri.p2 = vec3(1.0, 0.0, 10.0);
	TIntersection inter = intersectWithTriangle(parCamera, tri);
	if(inter.isValid)
	{
		return vec4(1.0,0.0,0.0,1.0);
	}
	return vec4(0.0,0.0,0.0,1.0);

}
void main()
{
	vec3 pointScreen = (coinInfGauche + texCoord.x * hauteurEcran * unitX*2.0*ratio + texCoord.y * hauteurEcran * unitY*2.0).xyz;
	frag_color = rayTrace(TRay(cameraPosition, normalize(pointScreen)))+vec4(0.1,0.1,0.1,0.0);
	// frag_color = rayTrace2(TRay(cameraPosition, normalize(pointScreen)));
    // frag_color = vec4( texCoord,0.0,1.0);
    // frag_color = sreen;
    // frag_color = unitY;
    // frag_color = vec4(normalize(pointScreen), 1.0);
    // frag_color = vec4(unpack(texture(points, vec2(0.01,0.39)).xyz),1.0);
}
