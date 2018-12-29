#include "phongmaterial.h"

PhongMaterial::PhongMaterial()
{
}

PhongMaterial::PhongMaterial( Color  _diffuse,  Color  _specular,  float _shininess)
{
	Ka = _diffuse.divide(100);
	diffuse = _diffuse;
	specular = _specular;
	shininess = _shininess;

}
PhongMaterial::PhongMaterial(Color _Ka, Color _diffuse, Color _specular, float _shininess)
{
	Ka = _Ka;
	diffuse = _diffuse;
	specular = _specular;
	shininess = _shininess;
}
PhongMaterial::PhongMaterial(Color _diffuse, Color _specular, float _shininess, float _reflectiveness)  {

	Ka = _diffuse.divide(100);
	diffuse = _diffuse;
	specular = _specular;
	shininess = _shininess;
	reflectiveness = _reflectiveness;

}
PhongMaterial::PhongMaterial(Color _Ka, Color _diffuse, Color _specular, float _shininess, float _reflectiveness)
{
	Ka = _Ka;
	diffuse = _diffuse;
	specular = _specular;
	shininess = _shininess;
	reflectiveness = _reflectiveness;
}
;
PhongMaterial::~PhongMaterial()
{
}
//  视线，交点位置，交点法向
Color PhongMaterial::sample(const CRay & _ray, const GVector3 & _position, GVector3 & _normal)
{



	//漫反射diffuse = Id•Kd• (N•L)

	float NdotL = _normal.dotMul(_lightray);
	Color diffuseTerm = this->diffuse.multiply(std::max(NdotL, 0.0f));

	//物体镜面反射specular = Is•Ks• (V·R)^n
	//R = 2(L•N)•N-L
	//V是相机方向向量，R是反射向量，­n­就反射强度Shininess
	/*为了提高计算效率，也可以利用HalfVectorH来计算镜面反射。
		specular = Is•Ks•(N•H)^n
		其中H = (L + V) / 2
		*/


	GVector3 H = (_lightray - _ray.getDirection()).normalize();
	float NdotH = _normal.dotMul(H);
	Color specularTerm = this->specular.multiply(pow(std::max(NdotH, (float)0), this->shininess));
	
	Color dif_spec = LightColor.modulate(diffuseTerm.add(specularTerm));
	Color ambient = LightColor.modulate(Ka);
	return dif_spec.add(ambient);
	//return dif_spec;
}

Color PhongMaterial::sample(const CRay & _ray, const CRay _lightray,const GVector3 & _position, GVector3 & _normal)
{
	//漫反射diffuse = Id•Kd• (N•L)

	float NdotL = _normal.dotMul(_lightray.getDirection().normalize());
	Color diffuseTerm = this->diffuse.multiply(std::max(NdotL, 0.0f));

	//物体镜面反射specular = Is•Ks• (V·R)^n
	//R = 2(L•N)•N-L
	//V是相机方向向量，R是反射向量，­n­就反射强度Shininess
	/*为了提高计算效率，也可以利用HalfVectorH来计算镜面反射。
	specular = Is•Ks•(N•H)^n
	其中H = (L + V) / 2
	*/


	GVector3 H = (_lightray.getDirection().normalize() - _ray.getDirection()).normalize();
	float NdotH = _normal.dotMul(H);
	Color specularTerm = this->specular.multiply(pow(std::max(NdotH, (float)0), this->shininess));

	Color dif_spec = LightColor.modulate(diffuseTerm.add(specularTerm));
	Color ambient = LightColor.modulate(Ka);
	return dif_spec.add(ambient);
}
