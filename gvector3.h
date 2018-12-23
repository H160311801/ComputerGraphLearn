#pragma once
#ifndef GVECTOR3_H
#define GVEVCTOR3_H
#include<iostream>
#include<cmath>
#define MIN(x,y) (x)>(y)?(y):(x);
#define MAX(x,y) (x)>(y)?(x):(y);
using namespace std;

class GVector3
{
public:

	float x;
	float y;
	float z;

	GVector3();
	~GVector3();

	GVector3(float posX, float posY, float posZ);
	void getInfo();//输出向量信息

	GVector3 operator+(const GVector3 &v);
	GVector3 operator-(const GVector3 &v);
	GVector3 operator*(float n);
	GVector3 operator/(float n);
	bool operator==(const GVector3 &v);

	float dotMul(const GVector3& v2);//向量点积
	GVector3 crossMul(const GVector3& v2);//叉乘
	GVector3 abs();
	float max();
	float min();
	float getLength();
	GVector3 normalize();//单位向量化
	float getDist(const GVector3 &v);
	static inline GVector3 zero() { return GVector3(0, 0, 0); }

	static GVector3 ZeroVec;
};


istream& operator>>(istream& in, GVector3& gvec);
ostream& operator<<(ostream& out, const GVector3& gvec);

#endif;//GVERCTOR3