#version 410

// Output vriables
out vec4 frag_color;

// Input variables
in vec2 texCoord;
in vec4 unitX;
in vec4 unitY;
in vec4 coinInfGauche;
in vec3 cameraPosition;

// Constants
#define focalDistance 50.0
#define MAX_VAL 1000000.0
#define EPSILON 0.00001
#define PI 3.14159265359

// Ratio indexes
const float NU = 1.3330;
//Absorption coefficient
const float SigA = 0.06911;
// scattering Coefficient
const float SigS = 1.0;
// Assymetry coefficient
const float g = 1.0;

const float hauteurEcran = 1.52638111*focalDistance;
const float ratio = 512.0/386.0;

float seed = 60.0;

// Uniforms
uniform int nbTriangles;
uniform sampler2D triangles;
uniform sampler2D texLego;

// Structures
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

// Misc 
float rand()
{
    return fract(sin(seed++)*43758.5453);
}

vec3 pdfUni(vec3 parNormal)
{
    float val = -1.0;
    vec3 wi;
    while(val>0.0)
    {
        float teta = 2.0*3.14*rand();
        float cosphi = (rand()*2.0 - 1.0);
        wi = vec3(sqrt(1.0-cosphi*cosphi)*cos(teta),sqrt(1.0-cosphi*cosphi)*sin(teta), cosphi);
        val = dot(wi, parNormal);
    }
    return wi;
}
// Textute management
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
	float delta;
	if(parI==nbTriangles)
		delta = -0.1;
	else
		delta = 0.1;
	float xVal = ((float(parI)+delta)/float(nbTriangles));
	parTriangle.p0 = unpack(texture(triangles, vec2(0.01,xVal)).xyz);
	parTriangle.n0 = unpack(texture(triangles, vec2(0.12,xVal)).xyz);
	parTriangle.uv0 = unpack(texture(triangles, vec2(0.23,xVal)).xy);

	parTriangle.p1 = unpack(texture(triangles, vec2(0.34,xVal)).xyz);
	parTriangle.n1 = unpack(texture(triangles, vec2(0.45,xVal)).xyz);
	parTriangle.uv1 = unpack(texture(triangles, vec2(0.56,xVal)).xy);

	parTriangle.p2 = unpack(texture(triangles, vec2(0.67,xVal)).xyz);
	parTriangle.n2 = unpack(texture(triangles, vec2(0.78,xVal)).xyz);
	parTriangle.uv2 = unpack(texture(triangles, vec2(0.89,xVal)).xy);
	return parTriangle;
}

// Subsurface scattering computation
float CPHI(float parN)
{
	float C1_2 = 0.0;
	if(parN<1.0)
	{
		C1_2 = 0.919317-3.4793*parN + 6.75335*pow(parN,2.0) - 7.80989*pow(parN,3.0) + 4.98554*pow(parN,4.0) - 1.36881*pow(parN,5.0);
	}
	else
	{
		C1_2 = -9.23372+22.2272*parN-20.9292*pow(parN,2.0)+10.2291*pow(parN,3.0)-2.54396*pow(parN,4.0)+0.254913*pow(parN,5.0);
	}
	return 0.25*(1.0-C1_2);
}
float CE(float parN)
{
	float C2_3 = 0.0;
	if(parN<1.0)
	{
		
		C2_3 = 0.828421-2.62051*parN + 3.36231*pow(parN,2.0) - 1.95284*pow(parN,3.0) + 0.236494*pow(parN,4.0) + 0.145787*pow(parN,5.0);
	}
	else
	{
		C2_3 = -1641.1 - 135.926/pow(parN,3.0)-656.175/pow(parN,2.0)+1376.53/parN+1213.67*parN-568.556*pow(parN,2.0)+164.798*pow(parN,3.0)-27.0181*pow(parN,4.0)+1.91826*pow(parN,5.0);
	}
	return 0.5*(1.0-C2_3);
}

float Spd(vec3 parX, vec3 parW12, float parR, vec3 parNO, float parD)
{
	float SigTR = sqrt(SigA/parD);
	float Term1 = (exp(-SigTR*parR)/(4.0*CPHI(1.0/NU)*4.0*PI*PI*pow(parR,3.0)));
	float Term2 = CPHI(NU)*(pow(parR,2.0)/parD+3.0*(1.0-SigTR*parR)*dot(parX, parW12));
	float Term3 = CE(NU)*(3.0*parD*(1.0+SigTR*parR)*dot(parNO,parW12)-((1.0+SigTR*parR)+3.0*parD*(3.0*(1.0+SigTR*parR)+pow((SigTR*parR),2.0))/pow(parR,2.0)*dot(parX, parW12))*dot(parX, parNO));
	return Term1*(Term2-Term3);
}
float Sd(vec3 parXi, vec3 parWi, vec3 parNi, TIntersection parInter)
{
	vec3 x0 = parInter.position;
	vec3 n0 = parInter.normal;
	vec3 w12 =  normalize(refract(-parWi, parNi, NU));
	float SigSp = (SigS*(1-g));
	float SigTp = SigSp+SigA;
	float D  = 1.0/(3.0*SigTp);
	float de = 2.131*D/sqrt(SigSp/SigTp);
	float theta = acos(dot(normalize(x0-parXi),w12));
	float r = length(x0-parXi);
	float cosBeta = -sin(theta)*r/(r*r+de*de);
	float NU0 = -dot(n0,w12);
	float dr = NU0>0.0?r*r+D*NU0*D*(NU0-2.0*de*cosBeta):r*r+D*D;
	vec3 XVECT = x0-parXi;
	vec3 nistar = cross(normalize(XVECT),normalize(cross(parNi,XVECT)));
	float A = (1.0-CE(NU))/CPHI(NU);
	vec3 xv = parXi+2.0*A*de*nistar;
	vec3 wv = w12-2.0*(dot(w12,nistar)*nistar);
	float dv = length(x0-xv);
	return (Spd(XVECT, w12, dr, n0, D) - Spd(x0-xv,wv,dv, n0, D));
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
TIntersection intersectWithScene(TRay parCamera)
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
	return finalIntersect;
}

vec4 pathTrace(TRay parCamera)
{
	TIntersection intersect = intersectWithScene(parCamera);
	if(intersect.isValid)
	{
		return vec4(intersect.uv,0.0,1.0);
	}
	else
		return vec4(0.0,0.0,0.0,1.0);

}
void main()
{
	// seed = ( iTime*30.0*gl_FragCoord.x/512.0+gl_FragCoord.y/386.0); 
	vec3 pointScreen = (coinInfGauche + texCoord.x * hauteurEcran * unitX*2.0*ratio - texCoord.y * hauteurEcran * unitY*2.0).xyz;
	frag_color = pathTrace(TRay(cameraPosition, normalize(pointScreen)));
}
