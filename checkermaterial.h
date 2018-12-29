#pragma once
#ifndef CHECKERMATERIAL_H
#define CHECKERMATERIAL_H
#include"material.h"

#include<stdlib.h>

class CheckerMaterial :public Material
{
private:
	float scale;
public:
	CheckerMaterial();
	CheckerMaterial(float _scale, float _reflectiveness = 0);
	virtual~CheckerMaterial();
	virtual Color sample(const CRay& _ray, const GVector3& _position,  GVector3& _normal);
	virtual Color sample(const CRay & _ray, const CRay _lightray, const GVector3 & _position, GVector3 & _normal);
};
#endif // !CHECKERMATERIAL_H
