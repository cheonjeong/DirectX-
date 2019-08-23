#pragma once
#include<cmath>
#include"cMatrix.h"
class cMatrix;
class cVector3
{

	
public:
	cVector3();
	~cVector3();

	float x, y, z;
	//>> : to do
	cVector3(float x, float y, float z) : x(x), y(y), z(z) {}
	
	//ºñ±³¿¬»êÀÚ
	bool operator==(cVector3 & vec);
	bool operator!=(cVector3 & vec);
	
	cVector3 operator+(cVector3 & vec);//µ¡¼À
	cVector3 operator-(cVector3 & vec);//»¬¼À
	cVector3 operator*(float f);//°ö¼À
	cVector3 operator/(float f);//³ª´°¼À
	

	static float Dot(cVector3& v1, cVector3& v2);//³»Àû
	static cVector3 Cross(cVector3 & v1, cVector3 & v2);//¿ÜÀû
	float length();//º¤ÅÍ Å©±â
	cVector3 Normalize();//º¤ÅÍ Á¤±ÔÈ­

	
	static cVector3 TransformCoord(cVector3 & v, cMatrix & mat);
	static cVector3 TransformNormal(cVector3 & v, cMatrix & mat);
};

