#pragma once
#include <GL/glut.h>
#include <vector>
#include <string>
#include <limits>

//#include "union.h"
#include "cobject.h"
#include "triangle.h"
#include "material.h"

using namespace std;

typedef GVector3 Vertex;
typedef Triangle Face;
typedef GVector3 nVec;


class ObjLoader: public CObject{
public:
	ObjLoader(string filename);

	//void draw();

	//Vertex getFocus();

	virtual IntersectResult isIntersected(CRay &_ray);

	void setMaterial(Material* material);

private:
	vector<Vertex> vSet;
	vector<Face> fSet;

	Vertex focus = Vertex();
	bool onlyDrawPoint = false;
};
