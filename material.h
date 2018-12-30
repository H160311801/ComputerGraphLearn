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
	float getRatio();
	void setReflec(float _reflectiveness);
	virtual ~Material();
	virtual Color sample(const CRay& _ray, const GVector3 &_position, GVector3 &_normal);
	virtual Color sample(const CRay & _ray, const CRay _lightray, const GVector3 & _position, GVector3 & _normal);
	
	Color Ka;//表面环境光反射系数假设为0.25
	Color diffuse;//扩散
	Color specular;//镜面
	float shininess;//
	float reflectiveness;
	float refractRatio = 0;//表面折射率，0，表示物体不透明
};

#endif // !MATERIAL_H
