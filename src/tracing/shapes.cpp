/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#include <tracing/shapes.h>
#include <butter/const.h>
#include <math.h>

namespace Donut
{
	#define EPSILON 0.0000001
	TTriangle::TTriangle()
	{

	}

	TTriangle::TTriangle(const TVertice& parV0, const TVertice& parV1, const TVertice& parV2)
	: v0(parV0)
	, v1(parV1)
	, v2(parV2)
	{

	}

	TIntersect TTriangle::intersect(const TRay& parRay)
	{
		TIntersect intersect;

	    Vector3 edge1 = v1.position - v0.position;
	    Vector3 edge2 = v2.position - v0.position;

	    Vector3 vecP = crossProd(parRay.direction,edge2);
	    float det = dotProd(edge1, vecP);

	    if(fabs(det)<EPSILON)
	    {
	        return intersect;
	    }

	    float invDet = 1.0 / det;
	    Vector3 vecS = parRay.origin - v0.position;

	    float u = dotProd(vecS, vecP) * invDet;
	    if(u<0.0 || u>1.0)
	        return intersect;

	    Vector3 vecQ = crossProd(vecS,edge1);
	    float v = dotProd(parRay.direction, vecQ) * invDet;
	    if(v<0.0f || u + v > 1.0f)
	        return intersect;

	    intersect.distance = dotProd(edge2, vecQ) * invDet;
	    Vector3 I = parRay.origin + parRay.direction*intersect.distance;

	    if(intersect.distance < EPSILON)
	        return intersect;
	    intersect.distance = fabs(intersect.distance);

	    // Calcul des données utiles
	    intersect.point.position = I;

	    intersect.point.uv = (v1.uv-v0.uv)*u+(v2.uv-v0.uv)*v+v0.uv;
	    Vector3 normal = (v1.normal-v0.normal)*u+(v2.normal-v0.normal)*v + v0.normal;

	    if(dotProd(parRay.direction, normal) > 0)
	        intersect.point.normal = -normal;
	    else
	        intersect.point.normal = normal;
	    intersect.isValid = true;

	    return intersect;
	}
}