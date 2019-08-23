#pragma once
#include"stdafx.h"
#include"cVector3.h"
class cVector3;
class cMatrix
{
public:
	cMatrix();
	~cMatrix();

private:
	class cRow//За
	{
	private:
		vector<float> m_col;//ї­
		int m_di;
	public:
		cRow();
		~cRow();
		cRow(int nDimension);
		

		void Resize(int nDimension);
		float & operator[] (int nIndex);
		vector<float> getVec() { return m_col; }
	};

	vector<cRow> m_vecData;


public:
	cMatrix(int nDimension);
	
	void Print();
	void Resize(int nDimension);
	int Dimension();

	static cMatrix Identity(int nDimension);
	cRow& operator[] (int nIndex);

	bool operator==(cMatrix & mat);
	bool operator!=(cMatrix & mat);

	cMatrix operator+(cMatrix & mat);
	cMatrix operator-(cMatrix & mat);
	cMatrix operator*(cMatrix & mat);
	cMatrix operator*(float f);

	cMatrix Inverse(OUT float & fDeterminant);
	float Determinant();
	cMatrix Adjoint();
	cMatrix Transpose();
	float Cofactor(int nRow, int nCol);
	float Minor(int nRow, int nCol);


public:
	static cMatrix Translation(float x, float y, float z);
	static cMatrix Translation(cVector3 & v);
	static cMatrix RotationX(float f);
	static cMatrix RotationY(float f);
	static cMatrix RotationZ(float f);

	static cMatrix View(cVector3 & vEye, cVector3 & vLookAt, cVector3 & vUp);
	static cMatrix Projection(float fFovY, float fAspect, float fNearZ, float fFarZ);

	static cMatrix ViewPort(float x, float y, float w, float h, float minz, float maxz);
	static cMatrix Scale(float a, float b, float c);

};

