#include "plane.h"

Plane::Plane()
{
}

Plane::Plane(const GVector3 & _normal, float _d)
{
	normal = _normal;
	d = _d;
}

Plane::~Plane()
{
}

GVector3 Plane::getNormal()
{
	return normal;
}

IntersectResult Plane::isIntersected(CRay & _ray)
{
	IntersectResult result = IntersectResult::noHit();
	result.object = this;
	float a = _ray.getDirection().dotMul(this->normal);
	if (a < 0)
	{
		result.isHit = 1;
		result.object = this;
		float b = this->normal.dotMul(_ray.getOrigin() - normal * d);
		result.distance = -b / a;
		result.position = _ray.getPoint(result.distance);
		result.normal = this->normal;
		
	}
	return result;
}
