#include "gvector3.h"

GVector3 GVector3::ZeroVec = GVector3(0.0f, 0.0f, 0.0f);

GVector3::GVector3()
{
}

GVector3::~GVector3()
{
}

GVector3::GVector3(float posX, float posY, float posZ)
{
	x = posX;
	y = posY;
	z = posZ;
}

void GVector3::getInfo()
{
	cout << "x:" << x << " y:" << y << " z:" << z << endl;
}

GVector3 GVector3::operator+(const GVector3 &v)
{
	
	return GVector3(x+v.x,y+v.y,z+v.z);
}

GVector3 GVector3::operator-(const GVector3 &v)
{
	return GVector3(x-v.x,y-v.y,z-v.z);
}

GVector3 GVector3::operator*(float n)
{
	return GVector3(x*n,y*n,z*n);
}

GVector3 GVector3::operator/(float n)
{
	return GVector3(x/n,y/n,z/n);
}

bool GVector3::operator==(const GVector3 &v)
{
	if(this->x!=v.x) return false;
	else if (this->y != v.y) return false;
	else if (this->z != v.z) return false;

	return true;
}



float GVector3::dotMul(const GVector3& v2)
{
	return (x*v2.x+y*v2.y+z*v2.z);
}

GVector3 GVector3::crossMul(const GVector3& v2)
{
	GVector3 result;
	result.x = ((y*v2.z) - (z*v2.y));
	result.y = ((z*v2.x) - (x*v2.z));
	result.z = ((x*v2.y) - (y*v2.x));
	return result;
}

GVector3 GVector3::abs()
{
	if (x < 0)x *= -1;
	if (y < 0)y *= -1;
	if (z < 0)z *= -1;
	return GVector3(x,y,z);
}

float GVector3::max()
{
	float temp = MAX(x, y);
	return MAX(temp,z);
}

float GVector3::min()
{
	float temp = MIN(x, y);
	return MIN(temp,z);
}

float GVector3::getLength()
{
	return (float)sqrt(x*x+y*y+z*z);
}

GVector3 GVector3::normalize()
{
	float length = getLength();
	x = x / length;
	y = y / length;
	z = z / length;
	return GVector3(x,y,z);
}

float GVector3::getDist(const GVector3 &v)
{
	return sqrt((x-v.x)*(x-v.x)+(y-v.y)*(y-v.y)+(z-v.z)*(z-v.z));
}

istream & operator>>(istream & in, GVector3 & gvec)
{
	in >> gvec.x >> gvec.y >> gvec.z;
	return in;
}

ostream & operator<<(ostream & out, const GVector3 & gvec)
{
	out << "x:" << gvec.x << " y:" << gvec.y << " z:" << gvec.z << endl;
	return out;
}
