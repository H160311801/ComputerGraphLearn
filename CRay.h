#pragma once
#ifndef CRAY_H
#define CRAY_H
#include<iostream>
#include"gvector3.h"
#define PI 3.14159
using namespace std;
class CRay
{
private:
	GVector3 origin;
	GVector3 direction;
public:
	CRay();
	~CRay();
	CRay(GVector3 ori, GVector3 dir);
	void setOrigin(GVector3 ori);
	void setDirection(GVector3 dir);
	GVector3 getOrigin();
	GVector3 getDirection()const;
	GVector3 getPoint(double t);//通过射线的参数方程传入参数t获得在射线上的点
};
#endif // !CRAY_H
