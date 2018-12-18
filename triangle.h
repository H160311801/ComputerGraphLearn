#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H
#include"cobject.h"

class Triangle : public CObject
{
public :
	Triangle();
	Triangle(GVector3 _A,GVector3 _B,GVector3 _C);
	Triangle(GVector3 _A, GVector3 _B, GVector3 _C,GVector3 _N);
	virtual ~Triangle();

	virtual IntersectResult isIntersected(CRay &_ray);
private:
	GVector3 vertexA;
	GVector3 vertexB;
	GVector3 vertexC;
	GVector3 normal;

};
#endif // !TRIANGLE_H

