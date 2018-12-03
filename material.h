#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H
#include "gvector3.h"
#include "IntersectResult.h"
#include"CRay.h"
#include"color.h"

class Material
{
public:
	Material();
	Material(float _reflectiveness);
	float getReflec();
	void setReflec(float _reflectiveness);
	virtual ~Material();
	virtual Color sample(const CRay& _ray, const GVector3 &_position,  GVector3 &_normal);
protected:
	float reflectiveness;
};

#endif // !MATERIAL_H
