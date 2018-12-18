#pragma once
#ifndef COLOR_H
#define COLOR_H
#include <stdlib.h>
#include <stdio.h>
#include<cmath>
#include<iostream>

using namespace std;
class Color
{
public:
	float R;
	float G;
	float B;
	Color();
	Color(float _R, float _G, float _B);
	Color add(const Color& c);
	Color multiply(float s)const;
	Color divide(float s)const;
	Color modulate(const Color&c)const;
	Color normalize();
	void saturate();
	void show();
	virtual ~Color();
	static inline Color black() { return Color(0, 0, 0); }
	static inline Color white() { return Color(1, 1, 1); }
	static inline Color red() { return Color(1, 0, 0); }
	static inline Color green() { return Color(0, 1, 0); }
	static inline Color blue() {	return Color(0, 0, 1);}
};
#endif // !COLOR_H
