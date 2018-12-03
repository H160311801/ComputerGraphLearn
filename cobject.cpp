#include "cobject.h"

CObject::CObject()
{
}

CObject::~CObject()
{
}

void CObject::setKa(GVector3 _Ka)
{
	m_Ka = _Ka;
}

void CObject::setKd(GVector3 _Kd)
{
	m_Kd = _Kd;
}

void CObject::setKs(GVector3 _Ks)
{
	m_Ks = _Ks;
}

void CObject::setShininess(double _Shininess)
{
	Shininess = _Shininess;
}

void CObject::setReflectivity(double _Reflectivity)
{
	Reflectivity = _Reflectivity;
}

GVector3 CObject::getKa()
{
	return m_Ka;
}

GVector3 CObject::getKd()
{
	return m_Kd;
}

GVector3 CObject::getKs()
{
	return m_Ks;
}

double CObject::getShininess()
{
	return Shininess;
}

double CObject::getReflectiviy()
{
	return Reflectivity;
}

GVector3 CObject::getNormal()
{
	return GVector3();
}

IntersectResult CObject::isIntersected(CRay & RAY)
{
	return IntersectResult();
}

//intersectresult cobject::isintersected(cray & ray)
//{
//	cout << "base cobject" << endl;
//}
