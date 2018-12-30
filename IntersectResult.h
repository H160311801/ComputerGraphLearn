#pragma once
#ifndef INTERSECTRESULT_H_INCLUDED
#define INTERSECTRESULT_H_INCLUDED
#include"gvector3.h"
//#include "cobject.h"
//#include"plane.h"
class CObject;
struct IntersectResult
{
	CObject* object;//交点所在的对象
	float distance;//到交点的距离
	bool isHit;	//是否相交
	GVector3 position;	//交点坐标
	GVector3 normal;	//交点法向
	static inline IntersectResult noHit() { return IntersectResult(); }
	IntersectResult() :object(NULL), isHit(false) {
	};
};
#endif // !INTERSECTRESULT_H_INCLUDED
