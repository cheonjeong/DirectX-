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
	
	//�񱳿�����
	bool operator==(cVector3 & vec);
	bool operator!=(cVector3 & vec);
	
	cVector3 operator+(cVector3 & vec);//����
	cVector3 operator-(cVector3 & vec);//����
	cVector3 operator*(float f);//����
	cVector3 operator/(float f);//������
	

	static float Dot(cVector3& v1, cVector3& v2);//����
	static cVector3 Cross(cVector3 & v1, cVector3 & v2);//����
	float length();//���� ũ��
	cVector3 Normalize();//���� ����ȭ

	
	static cVector3 TransformCoord(cVector3 & v, cMatrix & mat);
	static cVector3 TransformNormal(cVector3 & v, cMatrix & mat);
};

