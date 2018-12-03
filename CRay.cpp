#include "CRay.h"

CRay::CRay()
{
}

CRay::~CRay()
{
}

CRay::CRay(GVector3 ori, GVector3 dir)
{
	origin = ori;
	direction = dir;
}

void CRay::setOrigin(GVector3 ori)
{
	origin = ori;
}

void CRay::setDirection(GVector3 dir)
{
	direction = dir;
}

GVector3 CRay::getOrigin()
{
	return origin;
}

GVector3 CRay::getDirection() const
{
	return direction;
}

//GVector3 CRay::getDirection()
//{
//	return direction;
//}

GVector3 CRay::getPoint(double t)
{
	return origin+direction*t;
}
