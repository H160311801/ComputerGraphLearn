#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H
#include"cobject.h"

class Triangle : public CObject
{
public :
	Triangle();
	Triangle(const GVector3& _A, const GVector3& _B, const GVector3& _C);
	Triangle(const GVector3& _A, const GVector3& _B, const GVector3& _C, const GVector3& _N);
	virtual ~Triangle();

	virtual IntersectResult isIntersected(CRay &_ray);

	void setNormal(const GVector3& nvec);

private:
	GVector3 vertexA;
	GVector3 vertexB;
	GVector3 vertexC;
	GVector3 normal;

};
#endif // !TRIANGLE_H

