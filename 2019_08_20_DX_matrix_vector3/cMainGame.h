#pragma once
#include"cVector3.h"
#include"cMatrix.h"
#include"cGrid.h"

class cMainGame
{
public:
	cMainGame();
	~cMainGame();


private:
	HDC					m_memDC;
	HBITMAP				m_hBitmap, m_hOldBitmap;

	vector<cVector3>	m_vecVertex;
	vector<DWORD>		m_vecIndex;
	vector<cVector3>	m_vecLineVertex;

	cMatrix				m_matWorld;
	cMatrix				m_matView;
	cMatrix				m_matProj;
	cMatrix				m_matViewPort;


	cVector3			m_vEye;
	cVector3			m_vLookAt;
	cVector3			m_vUp;


	cVector3			m_vPosition;
	cVector3			m_vBoxDirection;

	float				m_fCameraDistance;
	bool				m_isRbutton;
	cVector3			m_vCamRotAngle;
	POINT				m_ptPrevMouse;

	cVector3			m_vAxisXTextPosition;
	cVector3			m_vAxisZTextPosition;

	float				m_jump;
	bool				m_flag;

public:
	void Setup();
	void Update();
	void Render(HDC hdc);
	void WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
private:
	float x;
	float y;
	float z;

	float look_x, look_y, look_z;
	cVector3 pos;
	float size_x, size_y, size_z;
public:
	void progress();
	void SetGrid();
	void DrawGrid();

	bool IsBackFace(cVector3 & v1, cVector3 & v2, cVector3 & v3);
};

