#include "union.h"

Union::Union()
{
}

Union::~Union()
{
}

void Union::push(CObject * _object)
{
	cobjects.push_back(_object);
}

IntersectResult Union::isIntersected(CRay & _ray)
{
	const float Infinity = 1e30f;
	float minDistance = Infinity;
	IntersectResult minResult = IntersectResult::noHit();
	long size = this->cobjects.size();
	for (long i = 0; i < size; i++)
	{
		IntersectResult result = this->cobjects[i]->isIntersected(_ray);
		if (result.isHit && (result.distance < minDistance))
		//if (result.distance < minDistance)
		{
			//cout << "aaa" << endl;
			minResult.object = this->cobjects[i];
			minDistance = result.distance;
			minResult = result;
			//minResult.object = result.object;
		}
	}
	return minResult;
}
