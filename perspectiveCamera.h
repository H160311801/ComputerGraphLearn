#pragma once
#ifndef PARSPECTIVECAMERA_H
#define PARSPECTIVECAMERA_H
#include "CRay.h"

class PerspectiveCamera
{
private:
	GVector3 eye;
	GVector3 front;
	GVector3 refup;
	GVector3 right;
	GVector3 up;
	float fov;
	float fovScale;
public:
	PerspectiveCamera();
	~PerspectiveCamera();
	PerspectiveCamera(const GVector3& _eye, const GVector3& _front, const GVector3& _refup, float _fov);
	CRay generateRay(float x, float y);

};
#endif // !PARSPECTIVECAMERA_H
