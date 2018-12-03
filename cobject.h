#pragma once
#ifndef COBJECT_H
#define COBJECT_H
#include"CRay.h"
#include"material.h"
#include"IntersectResult.h"

class CObject
{
public:
	Material*material=NULL;
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
	GVector3 m_Ka;
	GVector3 m_Kd;
	GVector3 m_Ks;
	double Shininess;
	double Reflectivity;
	
};
#endif // !COBJECT_H
