#pragma once
#ifndef PHONGMATERIAL_H
#define PHONGMATERIAL_H
#include"gvector3.h"
#include"color.h"
#include"CRay.h"
#include"material.h"
#include<algorithm>

//
static GVector3 _lightray = GVector3(-1, -1, -1).normalize();
static Color LightColor = Color::white();

static Color dauflt_Ka = Color(0.1, 0.1, 0.1);
class PhongMaterial:public Material
{
public:
	PhongMaterial();
	PhongMaterial( Color _diffuse,  Color specular, float _shininess);
	PhongMaterial(Color _Ka, Color _diffuse, Color _specular, float _shininess);
	PhongMaterial(Color _diffuse, Color _specular, float _shininess, float _reflectiveness);
	PhongMaterial(Color _Ka,Color _diffuse, Color _specular, float _shininess, float _reflectiveness);

	virtual~PhongMaterial();
	virtual Color sample(const CRay&_ray, const GVector3 &_position,  GVector3&_normal);
	virtual Color sample(const CRay & _ray, const CRay _lightray, const GVector3 & _position, GVector3 & _normal);
private:

}
#endif // !PHONGMATERIAL_H
;
