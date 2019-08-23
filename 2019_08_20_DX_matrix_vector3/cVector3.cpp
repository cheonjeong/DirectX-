#include "stdafx.h"
#include "cVector3.h"


cVector3::cVector3()
{
}


cVector3::~cVector3()
{
}


bool cVector3::operator==(cVector3 & vec)
{
	if(x - EPSILON <= vec.x && vec.x <= x+EPSILON &&
		y - EPSILON <= vec.y && vec.y <= y+EPSILON &&
		z - EPSILON <= vec.y && vec.z <= z + EPSILON)
		return true;
	else
		return false;
}

bool cVector3::operator!=(cVector3 & vec)
{
	if (x == vec.x || y == vec.y || z == vec.z) return false;
	else
		return true;
}

cVector3 cVector3::operator+(cVector3 & vec)
{
	cVector3 plus;
	plus.x = x + vec.x;
	plus.y = y + vec.y;
	plus.z = z + vec.z;
	return plus;
}


cVector3 cVector3::operator-(cVector3 & vec)
{
	cVector3 Minus;
	Minus.x = x - vec.x;
	Minus.y = y - vec.y;
	Minus.z = z - vec.z;
	return Minus;
}

cVector3 cVector3::operator*(float f)//½ºÄ®¶ó°ö
{
	cVector3::x = cVector3::x * f;
	cVector3::y = cVector3::y * f;
	cVector3::z = cVector3::z * f;
	return *this;
}

cVector3 cVector3::operator/(float f)//½ºÄ®¶ó ³ª´°¼À
{
	cVector3::x = cVector3::x / f;
	cVector3::y = cVector3::y / f;
	cVector3::z = cVector3::z / f;
	return *this;
}

float cVector3::Dot(cVector3 & v1, cVector3 & v2)//³»Àû
{
	float scalar = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return scalar;
}

cVector3 cVector3::Cross(cVector3 & v1, cVector3 & v2)//¿ÜÀû
{
	cVector3 vec;
	vec.x = (v1.y * v2.z) - (v1.z * v2.y);
	vec.y = (v1.z * v2.x) - (v1.x * v2.z);
	vec.z = (v1.x * v2.y) - (v1.y * v2.x);
	return vec;
}

float cVector3::length()//Å©±â
{
	float length = (float)sqrt(x*x + y*y + z*z);
	return length;
}

cVector3 cVector3::Normalize()//Á¤±ÔÈ­
{
	float length = sqrt(x*x + y*y + z*z);
	x = x / length; 
	y = y / length; 
	z = z / length;
	return *this;
}

cVector3 cVector3::TransformCoord(cVector3 & v, cMatrix & mat)
{
	cVector3 vRet;
	vRet.x = v.x * mat[0][0] + v.y * mat[1][0] + v.z * mat[2][0] + 1.0f * mat[3][0];
	vRet.y = v.x * mat[0][1] + v.y * mat[1][1] + v.z * mat[2][1] + 1.0f * mat[3][1];
	vRet.z = v.x * mat[0][2] + v.y * mat[1][2] + v.z * mat[2][2] + 1.0f * mat[3][2];
	float w = v.x * mat[0][3] + v.y * mat[1][3] + v.z * mat[2][3] + 1.0f * mat[3][3];

	if (-EPSILON > w || w > EPSILON)
	{
		vRet.x /= w;
		vRet.y /= w;
		vRet.z /= w;
	}
	return vRet;
}

cVector3 cVector3::TransformNormal(cVector3 & v, cMatrix & mat)
{
	cVector3 vRet;
	vRet.x = v.x * mat[0][0] + v.y * mat[1][0] + v.z * mat[2][0];
	vRet.y = v.x * mat[0][1] + v.y * mat[1][1] + v.z * mat[2][1];
	vRet.x = v.x * mat[0][2] + v.y * mat[1][2] + v.z * mat[2][2];
	
	return vRet;
}
