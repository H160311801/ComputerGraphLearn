#include "PointLight.h"

PointLight::PointLight()
{
}


PointLight::~PointLight()
{

}
PointLight::PointLight(Color _color, GVector3 _position, bool _isShadow)
{
	color = _color;
	position = _position;
	isShadow = _isShadow;
}

GVector3 PointLight::getPosition()
{
	return position;
}

////通过光线与场景的相交结果计算光照结果
//Color PointLight::intersect(Union* scence, IntersectResult &rayResult)
//{
//	//生产shadowRay的修正值
//	const float k = 1e-4;
//	GVector3 delta = this->position - rayResult.position;
//	float distance = delta.getLength();
//	//生成与光照相反方向的shadowRay
//	CRay shadowRay = CRay(rayResult.position, delta.normalize());
//	GVector3 shadowDir = delta.normalize();
//	//计算shadowRay是否与场景相交
//	IntersectResult lightResult = scence->isIntersected(shadowRay);
//	Color resultColor = Color::black();
//	Color returnColor = Color::black();
//	//如果shadowRay与场景中的物体相交
//	if (lightResult.object && (lightResult.distance <= distance))
//	{
//		return resultColor;
//	}
//	else
//	{
//		resultColor = this->color.divide(distance*distance);//点光源在此交点的光强
//		float NdotL = rayResult.normal.dotMul(shadowDir);
//		if (NdotL >= 0)
//			returnColor = returnColor.add(resultColor.multiply(NdotL));
//		return returnColor;
//	}
//
//}

Color PointLight::intersect(CObject* scence, IntersectResult &rayResult)
{
	//生产shadowRay的修正值
	const float k = 1e-4;
	GVector3 delta = this->position - rayResult.position;
	float distance = delta.getLength();
	//生成与光照相反方向的shadowRay
	CRay shadowRay = CRay(rayResult.position, delta.normalize());
	GVector3 shadowDir = delta.normalize();
	//计算shadowRay是否与场景相交
	IntersectResult lightResult = scence->isIntersected(shadowRay);
	Color resultColor = Color::black();
	Color returnColor = Color::black();
	//如果shadowRay与场景中的物体相交//如果交到物体，物体不为透明
	if (lightResult.object && (lightResult.object->material->getRatio() == 0.0)&& (lightResult.distance <= distance))// 
	{
		return returnColor;
	}
	else
	{
		if (lightResult.object)
		{
			resultColor = this->color.divide(distance*distance).multiply(0.3);//点光源在此交点的光强//有透明物体的时候
		}else
		resultColor = this->color.divide(distance*distance);//点光源在此交点的光强
		//returnColor = resultColor;
		float NdotL = rayResult.normal.dotMul(shadowDir);
		if (NdotL >= 0)
			returnColor = returnColor.add(resultColor.multiply(NdotL));
		return returnColor;
	}

}
