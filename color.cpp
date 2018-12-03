#include "color.h"

Color::Color()
{
}

Color::Color(float _R, float _G, float _B)
{
	R = _R;
	G = _G;
	B = _B;
}

Color Color::add(const Color & c)
{
	return Color(R+c.R,G+c.G,B+c.B);
}

Color Color::multiply(float s) const
{
	return Color(R*s,G*s,B*s);
}

Color Color::modulate(const Color & c) const
{
	return Color(R*c.R,G*c.G,B*c.B);
}

void Color::saturate()
{
	R = R > 1 ? 1:R;
	G = G > 1 ? 1 : G;
	B = B > 1 ? 1 : B;
}

void Color::show()
{
	cout << "R_G_B:" << R << "_$_" << G << "_$_" << B << endl;
}

Color::~Color()
{
}
