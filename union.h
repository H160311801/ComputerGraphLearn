#pragma once
#ifndef UNION_H
#define UNION_H
#include"cobject.h"
#include<vector>
using namespace std;

class Union :public CObject
{
public:
	Union();
	virtual~Union();

	void push(CObject* _object);
	virtual IntersectResult isIntersected(CRay& _ray);
private:
	vector<CObject*> cobjects;

};
#endif // !UNION_H

