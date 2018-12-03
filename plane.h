#pragma once
#ifndef Plane_H
#define Plane_H


#include"cobject.h"

class Plane:public CObject
{
public:
	//Material* material;
	Plane();
	Plane(const GVector3&_normal, float _d);
	virtual ~Plane();
	virtual GVector3 getNormal();
	virtual IntersectResult isIntersected(CRay& _ray);
private:
	GVector3 normal;
	float d;//��ԭ��ľ���;
};

#endif // !Plane_H
