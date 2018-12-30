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
	//IntersectResult result = IntersectResult::noHit();
	//GVector3 v = _ray.getOrigin() - center;//
	//float a =(float)( v.dotMul(v) - radius * radius);
	//float DdotV = _ray.getDirection().dotMul(v);
	//result.object = NULL;

	//if (DdotV <= 0)
	//{
	//	float discr = DdotV * DdotV - a;
	//	if (discr >= 0)
	//	{
	//		result.isHit = 1;
	//		result.distance = -DdotV - sqrt(discr);
	//		result.position = _ray.getPoint(result.distance);
	//		result.normal = result.position - center;
	//		result.normal.normalize();
	//		result.object = this;
	//	}
	//}
	//return result;
	IntersectResult result = IntersectResult::noHit();
		
		float t0, t1;
		float radiusSquare = this->radius*this->radius;
		GVector3 oc = this->center - _ray.getOrigin();
		float projoc = _ray.getDirection().dotMul(oc); 

		if (projoc < 0)
			return result;

		float oc2 = oc.dotMul(oc);
		float distance2 = oc2 - projoc * projoc;   //计算出的球心到射线的距离

		//if (distance2 > sphere.GetRadiusSquare())
		if (distance2 > radiusSquare)
		return result;

		float discriminant = radiusSquare - distance2;  //使用勾股定理，计算出另一条边的长度
		if (discriminant < 1e-5)   //表明只有一个交点，射线与球相切
		{
			t0 = t1 = projoc;
			result.isHit = 1;
			result.distance = t0;
			result.position = _ray.getPoint(result.distance);
			result.normal = result.position - center;
			result.normal.normalize();
			result.object = this;
		}
		else
		{
			discriminant = sqrt(discriminant);
			t0 = projoc - discriminant;
			t1 = projoc + discriminant;
			if (t0 <= 0)
				t0 = t1;
			result.isHit = 1;
			result.distance = t0;
			result.position = _ray.getPoint(result.distance);
			result.normal = result.position - center;
			result.normal.normalize();
			result.object = this;
		}
		return result;
	

}

CSphere::~CSphere()
{
}
