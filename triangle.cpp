#include "triangle.h"

Triangle::Triangle()
{
}

Triangle::Triangle(const GVector3& _A, const GVector3& _B, const GVector3& _C)
{
	vertexA = _A;
	vertexB = _B;
	vertexC = _C;
	normal = (vertexB - vertexA).crossMul(vertexC - vertexA);
}

Triangle::Triangle(const GVector3& _A, const GVector3& _B, const GVector3& _C, const GVector3& _N)
{
	vertexA = _A;
	vertexB = _B;
	vertexC = _C;
	normal = _N;
}

Triangle::~Triangle()
{
}

IntersectResult Triangle::isIntersected(CRay & _ray)
{
	IntersectResult result = IntersectResult::noHit();
	
	if(this->normal==GVector3(0.0f,0.0f,0.0f))// triangle is degenerate退化
	return result;

	//射线与平面法向量夹角
	float angle = this->normal.dotMul(_ray.getDirection());
	if (fabs(angle) < 1e-5) // fabs绝对值 //与光线平行
		return result;
	//
	GVector3 ori_vA = _ray.getOrigin() - this->vertexA;
	float a = -(this->normal.dotMul(ori_vA));

	float r = a / angle;
	if (r < 0.0f)
		return result; //未相交

	GVector3 interPoint = _ray.getOrigin() + _ray.getDirection()*r;

	//判断交点是否在三角形内部
	GVector3 edge1 = this->vertexB - this->vertexA;
	GVector3 edge2 = this->vertexC - this->vertexA;

	float edg11 = edge1.dotMul(edge1);
	float edg12= edge1.dotMul(edge2);
	float edg22 = edge2.dotMul(edge2);
	GVector3 w = interPoint - this->vertexA;

	float w_edg1 = w.dotMul(edge1);
	float w_edg2 = w.dotMul(edge2);

	float D = edg12 * edg12 - edg11 * edg22;

	float s = (edg12*w_edg2 - edg22 * w_edg1) / D;

	if(s<0.0f||s>1.0f)   //在三角形外部
		return result;

	float t = (edg12*w_edg1 - edg11 * w_edg2) / D;
	if(t<0.0f||(s+t)>1.0f)		//在三角形外部
		return result;

	result.isHit = 1;
	result.distance = _ray.getDirection().getLength()*r;
	result.position = interPoint;
	result.normal = this->normal;
	result.object = this;
		return  result;

}

void Triangle::setNormal(const GVector3 & nvec)
{
	normal = nvec;
}
