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

////ͨ�������볡�����ཻ���������ս��
//Color PointLight::intersect(Union* scence, IntersectResult &rayResult)
//{
//	//����shadowRay������ֵ
//	const float k = 1e-4;
//	GVector3 delta = this->position - rayResult.position;
//	float distance = delta.getLength();
//	//����������෴�����shadowRay
//	CRay shadowRay = CRay(rayResult.position, delta.normalize());
//	GVector3 shadowDir = delta.normalize();
//	//����shadowRay�Ƿ��볡���ཻ
//	IntersectResult lightResult = scence->isIntersected(shadowRay);
//	Color resultColor = Color::black();
//	Color returnColor = Color::black();
//	//���shadowRay�볡���е������ཻ
//	if (lightResult.object && (lightResult.distance <= distance))
//	{
//		return resultColor;
//	}
//	else
//	{
//		resultColor = this->color.divide(distance*distance);//���Դ�ڴ˽���Ĺ�ǿ
//		float NdotL = rayResult.normal.dotMul(shadowDir);
//		if (NdotL >= 0)
//			returnColor = returnColor.add(resultColor.multiply(NdotL));
//		return returnColor;
//	}
//
//}

Color PointLight::intersect(CObject* scence, IntersectResult &rayResult)
{
	//����shadowRay������ֵ
	const float k = 1e-4;
	GVector3 delta = this->position - rayResult.position;
	float distance = delta.getLength();
	//����������෴�����shadowRay
	CRay shadowRay = CRay(rayResult.position, delta.normalize());
	GVector3 shadowDir = delta.normalize();
	//����shadowRay�Ƿ��볡���ཻ
	IntersectResult lightResult = scence->isIntersected(shadowRay);
	Color resultColor = Color::black();
	Color returnColor = Color::black();
	//���shadowRay�볡���е������ཻ//����������壬���岻Ϊ͸��
	if (lightResult.object && (lightResult.object->material->getRatio() == 0.0)&& (lightResult.distance <= distance))// 
	{
		return returnColor;
	}
	else
	{
		if (lightResult.object)
		{
			resultColor = this->color.divide(distance*distance).multiply(0.3);//���Դ�ڴ˽���Ĺ�ǿ//��͸�������ʱ��
		}else
		resultColor = this->color.divide(distance*distance);//���Դ�ڴ˽���Ĺ�ǿ
		//returnColor = resultColor;
		float NdotL = rayResult.normal.dotMul(shadowDir);
		if (NdotL >= 0)
			returnColor = returnColor.add(resultColor.multiply(NdotL));
		return returnColor;
	}

}
