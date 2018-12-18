#include "directlight.h"

DirectLight::DirectLight()
{
}

DirectLight::DirectLight(Color _color, GVector3 _direction, bool _isShadow)
{
	color = _color;
	direction = _direction;
	isShadow = _isShadow;
}

DirectLight::~DirectLight()
{
}

Color DirectLight::intersect(Union & scence, IntersectResult & rayResult)
{
	const float k = 1e-4;//修正值
	GVector3 shadowDir = direction.normalize()*-1;//光源反方向
	CRay shadowRay = CRay(rayResult.position + rayResult.normal*k, shadowDir);

	IntersectResult lightResult = scence.isIntersected(shadowRay);
	Color resultColor = Color::black();
	if (isShadow)
	{
		if (lightResult.isHit)
		{
			return resultColor;
		}
	}

	float NdotL = rayResult.normal.dotMul(shadowDir);
	if (NdotL >= 0) resultColor = resultColor.add(this->color.multiply(NdotL));
	return resultColor;
}
