#pragma once
#ifndef COBJECT_H
#define COBJECT_H
#include"CRay.h"
#include"material.h"
#include"IntersectResult.h"

class CObject
{
public:
	Material*material=new Material(0.2f);
	CObject();
	virtual~CObject();
	void setKa(GVector3 _Ka);
	void setKd(GVector3 _Kd);
	void setKs(GVector3 _Ks);
	void setShininess(double _Shininess);
	void setReflectivity(double _Reflectivity);
	GVector3 getKa();
	GVector3 getKd();
	GVector3 getKs();
	double getShininess();
	double getReflectiviy();
	virtual GVector3 getNormal();
	virtual IntersectResult isIntersected(CRay& _ray);

protected:
	GVector3 m_Ka;//物体表面环境光反射系数
	GVector3 m_Kd;//漫反射系数
	GVector3 m_Ks;//镜面反射系数
	double Shininess;//镜面反射强度
	double Reflectivity;//环境反射强度
	
};
#endif // !COBJECT_H
