#pragma once
#ifndef PHONGMATERIAL_H
#define PHONGMATERIAL_H
#include"gvector3.h"
#include"color.h"
#include"CRay.h"
#include"material.h"
#include<algorithm>

//
static GVector3 LightDir = GVector3(1, 1, 1).normalize();//环境光
static Color LightColor = Color::white();//环境光
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
private:
	Color Ka ;//表面环境光反射系数假设为0.25
	Color diffuse;//扩散
	Color specular;//镜面
	float shininess;//
}
#endif // !PHONGMATERIAL_H
;
