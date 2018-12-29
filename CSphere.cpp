#include "CSphere.h"

CSphere::CSphere()
{
}

CSphere::CSphere(GVector3 cen, double rad)
{
	center = cen;
	radius = rad;
}

CSphere::CSphere(CSphere & a)
{
	center = a.getCenter();
	radius = a.getRadius();
}

void CSphere::setCenter(GVector3 & cen)
{
	center = cen;
}

void CSphere::setRadius(double r)
{
	radius = r;
}

GVector3 CSphere::getCenter()
{
	return center;
}

double CSphere::getRadius()
{
	return radius;
}

GVector3 CSphere::getNormal(GVector3 point)
{
	return point-center;
}

IntersectResult CSphere::isIntersected(CRay& _ray)
{
	IntersectResult result = IntersectResult::noHit();
	GVector3 v = _ray.getOrigin() - center;
	float a =(float)( v.dotMul(v) - radius * radius);
	float DdotV = _ray.getDirection().dotMul(v);
	result.object = NULL;

	if (DdotV <= 0)
	{
		float discr = DdotV * DdotV - a;
		if (discr >= 0)
		{
			result.isHit = 1;
			result.distance = -DdotV - sqrt(discr);
			result.position = _ray.getPoint(result.distance);
			result.normal = result.position - center;
			result.normal.normalize();
			result.object = this;
		}
	}
	return result;
}

CSphere::~CSphere()
{
}
