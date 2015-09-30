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
#include <math/const.h>
#include <math.h>

namespace Donut
{
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

	    TVec3 edge1 = v1.position - v0.position;
	    TVec3 edge2 = v2.position - v0.position;

	    TVec3 vecP = parRay.direction^edge2;
	    float det = dot(edge1, vecP);

	    if(fabs(det)<EPSILON)
	    {
	        return intersect;
	    }

	    float invDet = 1.0 / det;
	    TVec3 vecS = parRay.origin - v0.position;

	    float u = dot(vecS, vecP) * invDet;
	    if(u<0.0 || u>1.0)
	        return intersect;

	    TVec3 vecQ = vecS^edge1;
	    float v = dot(parRay.direction, vecQ) * invDet;
	    if(v<0.0f || u + v > 1.0f)
	        return intersect;

	    intersect.distance = dot(edge2, vecQ) * invDet;
	    TVec3 I = parRay.origin + intersect.distance*parRay.direction;

	    if(intersect.distance < EPSILON)
	        return intersect;
	    intersect.distance = fabs(intersect.distance);

	    // Calcul des données utiles
	    intersect.point.position = I;

	    intersect.point.uv = u*(v1.uv-v0.uv)+v*(v2.uv-v0.uv)+v0.uv;
	    TVec3 normal = u*(v1.normal-v0.normal)+v*(v2.normal-v0.normal) + v0.normal;

	    if(dot(parRay.direction, normal) > 0)
	        intersect.point.normal = -normal;
	    else
	        intersect.point.normal = normal;
	    intersect.isValid = true;

	    return intersect;
	}
}