#include "checkermaterial.h"

CheckerMaterial::CheckerMaterial()
{

}
CheckerMaterial::CheckerMaterial(float _scale, float _reflectiveness)
{
	scale = _scale;
	reflectiveness = _reflectiveness;
}

CheckerMaterial::~CheckerMaterial()
{
}

Color CheckerMaterial::sample(const CRay & _ray, const GVector3 & _position,  GVector3 & _normal)
{
	
	//floor向下取整
	float d = abs((floor(_position.x*this->scale) +floor(_position.z*this->scale)));
	d = fmod(d, 2);
	return d<1?Color::black():Color::white();
}

Color CheckerMaterial::sample(const CRay & _ray, const CRay _lightray, const GVector3 & _position, GVector3 & _normal)
{
	return Color();
}
