#include"stdafx.h"
#include "cMatrix.h"

cMatrix::cMatrix()
{
}


cMatrix::~cMatrix()
{
}

cMatrix::cRow::cRow()
{
}

cMatrix::cRow::~cRow()
{
}

cMatrix::cRow::cRow(int nDimension)
{
	Resize(nDimension);
}

void cMatrix::cRow::Resize(int nDimension)
{
	m_col.resize(nDimension);
}

float & cMatrix::cRow::operator[](int nIndex)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_col[nIndex];
}

cMatrix::cMatrix(int nDimension)
{
	Resize(nDimension);
}


void cMatrix::Print()
{
	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			printf("% 8.2f", (*this)[i][j]);
		}
		printf("\n");
	}
}

void cMatrix::Resize(int nDimension)
{
	m_vecData.resize(nDimension);
	for (size_t i = 0; i < nDimension; i++)
		m_vecData[i].Resize(nDimension);
}

int cMatrix::Dimension()
{
	return (int)m_vecData.size();
}

cMatrix cMatrix::Identity(int nDimension) //해당 차수에 대한 항등 행렬
{
	cMatrix matRet(nDimension);
	for (int i = 0; i < nDimension; i++)
	{
		for (int j = 0; j < nDimension; j++)
		{
			matRet[i][j] = (i == j) ? 1 : 0;
		}
	}
	return matRet;
}

cMatrix::cRow & cMatrix::operator[](int nIndex)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_vecData[nIndex];
}

bool cMatrix::operator==(cMatrix & mat)
{
	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			if ((*this)[i][j] - EPSILON > mat[i][j])
				return false;
			if ((*this)[i][j] + EPSILON < mat[i][j])
				return false;
		}
	}
	return true;
}

bool cMatrix::operator!=(cMatrix & mat)
{
	return !((*this) == mat );
}

cMatrix cMatrix::operator+(cMatrix & mat)
{
	cMatrix matRet(Dimension());
	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			matRet[i][j] = (*this)[i][j] + mat[i][j];
		}
	}
	return matRet;
}

cMatrix cMatrix::operator-(cMatrix & mat)
{
	cMatrix matRet(Dimension());
	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			matRet[i][j] = (*this)[i][j] - mat[i][j];
		}
	}
	return matRet;
}

cMatrix cMatrix::operator*(cMatrix & mat)
{

	cMatrix matRet(Dimension());
	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			matRet[i][j] = 0.f;
			for (int k = 0; k < Dimension(); k++)
			{
				matRet[i][j] += ((*this)[i][k] * mat[k][j]);
			}
		}
	}
	return matRet;
}

cMatrix cMatrix::operator*(float f)
{
	cMatrix matRet(Dimension());
	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			matRet[i][j] = (*this)[i][j] * f;
		}
	}
	return matRet;
}

cMatrix cMatrix::Inverse(OUT float & fDeterminant)
{
	cMatrix matRet = cMatrix::Identity(Dimension());

	fDeterminant = Determinant();


	if (-EPSILON < fDeterminant && fDeterminant < EPSILON)
	{
		cout << "역행렬이 존재 하지 않음" << endl;
		return matRet;
	}
	cMatrix matAdj = Adjoint();

	matRet = matAdj * (1 / fDeterminant);

	return matRet;
}

float cMatrix::Determinant()
{
	if (Dimension() == 2)
		return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];

	float fDeterminant = 0.0f;

	for (int i = 0; i < Dimension(); i++)
	{
		fDeterminant += ((*this)[i][0] * Cofactor(i, 0));
	}

	return fDeterminant;
}

cMatrix cMatrix::Adjoint()//cofactor에 대한 전치
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			matRet[i][j] = Cofactor(j, i);
		}
	}
	return matRet;
}

cMatrix cMatrix::Transpose() // 전치
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			matRet[i][j] = (*this)[j][i];
		}
	}

	return matRet;
}

float cMatrix::Cofactor(int nRow, int nCol)
{
	int nConst = 1;
	if ((nRow + nCol) % 2 != 0)
		nConst = -1;
	
	return nConst * Minor(nRow, nCol);
}

float cMatrix::Minor(int nRow, int nCol)
{
	cMatrix matMinor(Dimension() - 1);

	int nMinorRow = 0;
	int nMinorCol = 0;

	for (int i = 0; i < Dimension(); i++)
	{
		if (nRow == i)
			continue;
		nMinorCol = 0;

		for (int j = 0; j < Dimension(); j++)
		{
			if (nCol == j)
				continue;
			matMinor[nMinorRow][nMinorCol] = (*this)[i][j];
			++nMinorCol;
		}
		++nMinorRow;
	}
	return matMinor.Determinant();
}



//큐브 만들기
cMatrix cMatrix::Translation(float x, float y, float z)
{
	cMatrix Translate = cMatrix::Identity(4);
	Translate[3][0] = x;
	Translate[3][1] = y;
	Translate[3][2] = z;

	return Translate;
}

cMatrix cMatrix::Translation(cVector3 & v)
{
	cMatrix Translate = cMatrix::Identity(4);
	Translate[3][0] = v.x;
	Translate[3][1] = v.y;
	Translate[3][2] = v.z;

	return Translate;
}

cMatrix cMatrix::RotationX(float f)//x축으로 회전
{
	cMatrix Rotate = cMatrix::Identity(4);
	Rotate[1][1] = cos(f * (PI / 180));
	Rotate[1][2] = sin(f * (PI / 180));
	Rotate[2][1] = -sin(f * (PI / 180));
	Rotate[2][2] = cos(f * (PI / 180));
	return Rotate;
}

cMatrix cMatrix::RotationY(float f)//y축으로 회전
{
	cMatrix Rotate = cMatrix::Identity(4);
	Rotate[0][0] = cos(f * (PI / 180));
	Rotate[0][2] = -sin(f * (PI / 180));
	Rotate[2][0] = sin(f * (PI / 180));
	Rotate[2][2] = cos(f * (PI / 180));
	return Rotate;
}

cMatrix cMatrix::RotationZ(float f)//z축으로 회전
{
	cMatrix Rotate = cMatrix::Identity(4);
	Rotate[0][0] = cos(f * (PI / 180));
	Rotate[0][1] = sin(f * (PI / 180));
	Rotate[1][0] = -sin(f * (PI / 180));
	Rotate[1][1] = cos(f * (PI / 180));
	return Rotate;
}

cMatrix cMatrix::View(cVector3 & vEye, cVector3 & vLookAt, cVector3 & vUp)
{
	cVector3 l = (vLookAt - vEye).Normalize();// 0, -5, 5
	cVector3 r = cVector3::Cross(vUp, l).Normalize();
	cVector3 u = cVector3::Cross(l, r).Normalize();

	cMatrix matRet = cMatrix::Identity(4);
	matRet[0][0] = r.x; 
	matRet[0][1] = u.x; 
	matRet[0][2] = l.x;

	matRet[1][0] = r.y; 
	matRet[1][1] = u.y; 
	matRet[1][2] = l.y;

	matRet[2][0] = r.z; 
	matRet[2][1] = u.z; 
	matRet[2][2] = l.z;

	matRet[3][0] = -cVector3::Dot(r, vEye); 
	matRet[3][1] = -cVector3::Dot(u, vEye);
	matRet[3][2] = -cVector3::Dot(l, vEye);

	return matRet;
}

cMatrix cMatrix::Projection(float fFovY, float fAspect, float fNearZ, float fFarZ)
{
	cMatrix matRet = cMatrix::Identity(4);
	float fScaleY = 1.0f / tanf(fFovY / 2.0f);
	float fScaleX = fScaleY / fAspect;

	matRet[0][0] = fScaleX;
	matRet[1][1] = fScaleY;
	matRet[2][2] = fFarZ / (fFarZ - fNearZ);
	matRet[2][3] = 1.0f;
	matRet[3][2] = -fFarZ * fNearZ / (fFarZ - fNearZ);
	matRet[3][3] = 0.0f;

	return matRet;
}

cMatrix cMatrix::ViewPort(float x, float y, float w, float h, float minz, float maxz)
{
	cMatrix matRet = cMatrix::Identity(4);

	matRet[0][0] = w / 2.0f;
	matRet[1][1] = -h / 2.0f;
	matRet[2][2] = maxz - minz;
	matRet[3][0] = x + w / 2.0f;
	matRet[3][1] = y + h / 2.0f;
	matRet[3][2] = minz;

	return matRet;
}

cMatrix cMatrix::Scale(float a, float b, float c)
{
	cMatrix mat = cMatrix::Identity(4);
	mat[0][0] = a;
	mat[1][1] = b;
	mat[2][2] = c;
	return mat;
}