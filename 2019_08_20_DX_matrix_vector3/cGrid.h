#pragma once
#include"cVector3.h"
#include"cMatrix.h"
class cGrid
{
public:
	cGrid();
	~cGrid();
	void Render(HDC hdc, cMatrix & transform);
	cGrid(int row, int col);
private:
	cVector3 m_cVertex;
	vector<cVector3> vVertex_point;
	vector<UINT> vIn;
	static cVector3 i, j, k;
	int m_row, m_col, m_size;

	bool isDirty_;
};

