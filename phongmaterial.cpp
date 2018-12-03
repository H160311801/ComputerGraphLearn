#include "phongmaterial.h"

PhongMaterial::PhongMaterial()
{
}

PhongMaterial::PhongMaterial( Color  _diffuse,  Color  _specular,  float _shininess)
{
	diffuse = _diffuse;
	specular = _specular;
	shininess = _shininess;

}
PhongMaterial::PhongMaterial(Color _diffuse, Color _specular, float _shininess, float _reflectiveness)  {

	diffuse = _diffuse;
	specular = _specular;
	shininess = _shininess;
	reflectiveness = _reflectiveness;

};
PhongMaterial::~PhongMaterial()
{
}

Color PhongMaterial::sample(const CRay & _ray, const GVector3 & _position, GVector3 & _normal)
{
	float NdotL = _normal.dotMul(LightDir);
	GVector3 H = (LightDir - _ray.getDirection()).normalize();
	float NdotH = _normal.dotMul(H);
	Color diffuseTerm = this->diffuse.multiply(std::max(NdotL, 0.0f));
	Color specularTerm = this->specular.multiply(pow(std::max(NdotH, (float)0), this->shininess));
	

	return LightColor.modulate(diffuseTerm.add(specularTerm));
}
