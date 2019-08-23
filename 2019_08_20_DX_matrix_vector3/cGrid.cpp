#include "stdafx.h"
#include "cGrid.h"

cVector3 cGrid::i = cVector3(1.0f, 0.0f, 0.0f);

cVector3 cGrid::j = cVector3(0.0f, 1.0f, 0.0f);

cVector3 cGrid::k = cVector3(0.0f, 0.0f, 1.0f);
cGrid::cGrid()
{
}


cGrid::~cGrid()
{
}

cGrid::cGrid(int row, int col)
	:m_row(row), m_col(col), m_size(1), isDirty_(true)
{
	for (int r = 0; r < m_row; r++)
	{
		for (int c = 0; c < m_col; c++)
		{
			cVector3 vertex(m_cVertex.x + ((-m_row / 2) + r) * m_size, 
				0.0f, 
				m_cVertex.y + ((-m_col / 2) + c) * m_size);
			vVertex_point.push_back(vertex);
		}
	}
	for (int r = 0; r < m_row - 1; r++)
	{
		for (int c = 0; c < m_col - 1; c++)
		{
			vIn.push_back(m_col * r + c);
			vIn.push_back(m_col * r + c + 1);
			vIn.push_back(m_col * (r + 1) + c);

			vIn.push_back(m_col * r + c + 1);
			vIn.push_back(m_col * (r + 1) + c + 1);
			vIn.push_back(m_col * (r + 1) + c);
		}
	}
}

void cGrid::Render(HDC hdc, cMatrix & transform)
{

}
