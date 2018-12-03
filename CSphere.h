#pragma once
#ifndef CSPHERE_H
#define CSPHERE_H
#include"IntersectResult.h"
#include"gvector3.h"
#include"CRay.h"
//#include"phongmaterial.h"
#include"material.h"
#include"cobject.h"

class CSphere:public CObject
{
public:
	//PhongMaterial * material;
	//Material * material;
	CSphere();
	CSphere(GVector3 center, double radius);
	CSphere(CSphere& a);
	void setCenter(GVector3& cen);
	void setRadius(double r);
	GVector3 getCenter();
	double getRadius();

	virtual GVector3 getNormal(GVector3 point);//获取物体表面一点的法线
	virtual IntersectResult isIntersected(CRay &_ray);//判断射线和该物体交点
	virtual ~CSphere();
private:
	GVector3 center;
	double radius;
};
#endif // !CSPHERE_H
