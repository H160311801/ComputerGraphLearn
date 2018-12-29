#include "triangle.h"

Triangle::Triangle()
{
}

Triangle::Triangle(const GVector3& _A, const GVector3& _B, const GVector3& _C)
{
	vertexA = _A;
	vertexB = _B;
	vertexC = _C;
	normal = (vertexC - vertexA).crossMul(vertexB - vertexA).normalize();
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
if (angle>0||fabs(angle) < 1e-5) // fabs绝对值 //与光线平行//或者与视线与正面未相交
return result;


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




//IntersectResult Triangle::isIntersected(CRay & _ray)
//{
//	 Determine whether a ray intersect with a triangle
//	 Parameters
//	 orig: origin of the ray
//	 dir: direction of the ray
//	 v0, v1, v2: vertices of triangle
//	 t(out): weight of the intersection for the ray
//	 u(out), v(out): barycentric coordinate of intersection
//		
//	IntersectResult result = IntersectResult::noHit();
//
//		GVector3 orig = _ray.getOrigin();
//		GVector3 dir = _ray.getDirection();
//		 E1
//		GVector3 E1 = vertexB - vertexA;
//
//		 E2
//		GVector3 E2 = vertexC - vertexA;
//
//		 P
//		GVector3 P = dir.crossMul(E2);
//
//		 determinant
//		float det = E1.dotMul(P);
//
//		 keep det > 0, modify T accordingly
//		GVector3 T;
//		if (det >0)
//		{
//			T = orig - vertexA;
//		}
//		else
//		{
//			T = vertexA - orig;
//			det = -det;
//		}
//
//		 If determinant is near zero, ray lies in plane of triangle
//		if (det < 0.0001f)
//			return result;
//
//		 Calculate u and make sure u <= 1
//		float u = T.dotMul(P);
//		if (u < 0.0f || u > det)
//			return result;
//
//		 Q
//		GVector3 Q = T.crossMul(E1);
//
//		 Calculate v and make sure u + v <= 1
//		float v = dir.dotMul(Q);
//		if (v < 0.0f || u + v > det)
//			return result;
//
//		 Calculate t, scale parameters, ray intersects triangle
//		float t = E2.dotMul(Q);
//
//		float fInvDet = 1.0f / det;
//		t *= fInvDet;
//		u *= fInvDet;
//		v *= fInvDet;
//		result.isHit = true;
//		result.object = this;
//		result.normal = this->normal;
//		result.position = dir*v;
//		result.distance = dir.getLength()*v;
//		
//		return result;
//	
//}

void Triangle::setNormal(const GVector3 & nvec)
{
	normal = nvec;
}
