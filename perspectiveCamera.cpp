#include "perspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera()
{
}

PerspectiveCamera::~PerspectiveCamera()
{
}

PerspectiveCamera::PerspectiveCamera(const GVector3 & _eye, const GVector3 & _front, const GVector3 & _refup, float _fov)
{
	eye = _eye;
	front = _front;
	refup = _refup;
	fov = _fov;

	right = front.crossMul(refup);
	//right.getInfo();
	//right = refup;
	up = right.crossMul(front);

	//cout << "RefUp: " << refup << " Up: " << up << endl;
	//cout << "Is equal? (up and refup)" << (up == refup) << endl;

	fovScale = tan(fov*(3.14159*0.5f / 180))*2;
	//fovScale = tan(fov*(PI*0.5f / 180)) * front.getLength();

	front.getInfo();
	right.getInfo();
	up.getInfo();
}

CRay PerspectiveCamera::generateRay(float x, float y)
{
	GVector3 r = right * ((x - 0.5f)*fovScale);//减0.5是把摄像机采样坐标从【0，1】变换到【-1，1】
	GVector3 u = up * ((y - 0.5f)*fovScale);
	GVector3 tmp = front + r + u;
	//front.getInfo();
	//right.getInfo();
	//up.getInfo();
	//tmp.getInfo();
	//cout << tmp.getLength()<<endl;
	tmp.normalize();

	//eye.getInfo();
	//GVector3 a = GVector3(0, 10, -1).normalize();
	//return CRay(eye, a);
	return CRay(eye,tmp);
}
