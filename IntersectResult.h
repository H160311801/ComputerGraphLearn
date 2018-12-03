#pragma once
#ifndef INTERSECTRESULT_H_INCLUDED
#define INTERSECTRESULT_H_INCLUDED
#include"gvector3.h"
//#include "cobject.h"
//#include"plane.h"
class CObject;
struct IntersectResult
{
	
	//Plane object;
	//
	CObject* object;
	float distance;
	bool isHit;
	GVector3 position;
	GVector3 normal;
	static inline IntersectResult noHit() { return IntersectResult(); }
	IntersectResult() :object(NULL), isHit(false) {
	};
};
#endif // !INTERSECTRESULT_H_INCLUDED
