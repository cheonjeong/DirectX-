#include "stdafx.h"
#include "cMainGame.h"


cMainGame::cMainGame()
	:m_hOldBitmap(NULL), m_vEye(0, 0, -5), m_vLookAt(0, 0, 0), m_vUp(0, 1, 0),
	m_vPosition(0, 0, 0),
	m_vBoxDirection(0, 0, 1),
	m_fCameraDistance(5.0f),
	m_isRbutton(false),
	m_vCamRotAngle(0, 0, 0),
	m_jump(0.0f),
	m_flag(false)
{
}


cMainGame::~cMainGame()
{
	SelectObject(m_memDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_memDC);
}

void cMainGame::Setup()
{
	y = 0.0f;
	x = 0.0f;
	z = 0.0f;

	look_x = 0.0f;
	look_y = 0.0f;
	look_z = 0.0f;
	
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;

	size_x = 1.0f;
	size_y = 1.0f;
	size_z = 1.0f;
	
	HDC hdc = GetDC(g_hWnd);
	m_memDC = CreateCompatibleDC(hdc);
	{
		RECT rc;
		GetClientRect(g_hWnd, &rc);
		m_hBitmap = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		m_hOldBitmap = (HBITMAP)SelectObject(m_memDC, m_hBitmap);
		ReleaseDC(g_hWnd, hdc);
	}
	{
		//front
		m_vecVertex.push_back(cVector3(-1.0f, -1.0f, -1.0f));
		m_vecVertex.push_back(cVector3(-1.0f, 1.0f, -1.0f));
		m_vecVertex.push_back(cVector3(1.0f, 1.0f, -1.0f));
		m_vecVertex.push_back(cVector3(1.0f, -1.0f, -1.0f));

		//back
		m_vecVertex.push_back(cVector3(-1.0f, -1.0f, 1.0f));
		m_vecVertex.push_back(cVector3(-1.0f, 1.0f, 1.0f));
		m_vecVertex.push_back(cVector3(1.0f, 1.0f, 1.0f));
		m_vecVertex.push_back(cVector3(1.0f, -1.0f, 1.0f));
	}
	
	{
		//front
		m_vecIndex.push_back(0);
		m_vecIndex.push_back(1);
		m_vecIndex.push_back(2);

		m_vecIndex.push_back(0);
		m_vecIndex.push_back(2);
		m_vecIndex.push_back(3);
		//back
		m_vecIndex.push_back(4);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(5);

		m_vecIndex.push_back(4);
		m_vecIndex.push_back(7);
		m_vecIndex.push_back(6);
		
		//left
		m_vecIndex.push_back(4);
		m_vecIndex.push_back(5);
		m_vecIndex.push_back(1);
		
		m_vecIndex.push_back(4);
		m_vecIndex.push_back(1);
		m_vecIndex.push_back(0);
		
		//right
		m_vecIndex.push_back(3);
		m_vecIndex.push_back(2);
		m_vecIndex.push_back(6);
		
		m_vecIndex.push_back(3);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(7);
		
		//top
		m_vecIndex.push_back(1);
		m_vecIndex.push_back(5);
		m_vecIndex.push_back(6);

		m_vecIndex.push_back(1);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(2);
		//bottom
		m_vecIndex.push_back(4);
		m_vecIndex.push_back(0);
		m_vecIndex.push_back(3);

		m_vecIndex.push_back(4);
		m_vecIndex.push_back(3);
		m_vecIndex.push_back(7);
	}
	m_matWorld = cMatrix::Identity(4);
	m_matView = cMatrix::Identity(4);
	m_matProj = cMatrix::Identity(4);
	m_matViewPort = cMatrix::Identity(4);
}

void cMainGame::Update()
{
	RECT rc;
	if (m_flag)
	{
		m_jump += 0.5f;
		if (m_jump > 2.0f)
			m_flag = false;
	}
	if (!m_flag)
	{
		m_jump -= 0.5f;
		if (m_jump < 0.0f)
			m_jump = 0.0f;
	}
	
	GetClientRect(g_hWnd, &rc);
	m_vLookAt = cVector3(pos.x + look_x, pos.y + look_y, pos.z + look_z);
	m_vEye = cVector3(0.0f + pos.x, 5.0f + pos.y, -m_fCameraDistance + pos.z);

	cMatrix matRX = cMatrix::RotationX(m_vCamRotAngle.x);
	cMatrix matRY = cMatrix::RotationY(m_vCamRotAngle.y);
	cMatrix matCamR = matRX * matRY;//camera rotation
	
	m_vEye = cVector3::TransformCoord(m_vEye, matCamR);

	
	m_matWorld = cMatrix::Scale(size_x, size_y, size_z) * //크기 조절
		(cMatrix::RotationX(x) * cMatrix::RotationY(y) * cMatrix::RotationZ(z)) * //회전 조절
		cMatrix::Translation(pos.x, pos.y + m_jump, pos.z); //이동 조절

	m_matView = cMatrix::View(m_vEye, m_vLookAt, m_vUp);
	m_matProj = cMatrix::Projection(PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	m_matViewPort = cMatrix::ViewPort(0, 0, rc.right, rc.bottom, 0, 1);
}

void cMainGame::Render(HDC hdc)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	PatBlt(m_memDC, rc.left, rc.top, rc.right, rc.bottom, WHITENESS);

	cMatrix matWVP = m_matWorld * m_matView * m_matProj;
	for (size_t i = 0; i < m_vecIndex.size(); i += 3)
	{
		cVector3 v1 = m_vecVertex[m_vecIndex[i + 0]];
		cVector3 v2 = m_vecVertex[m_vecIndex[i + 1]];
		cVector3 v3 = m_vecVertex[m_vecIndex[i + 2]];

		v1 = cVector3::TransformCoord(v1, matWVP);
		v2 = cVector3::TransformCoord(v2, matWVP);
		v3 = cVector3::TransformCoord(v3, matWVP);

		// To Do SomeThing
		if (IsBackFace(v1, v2, v3))//backface culling
			continue;


		v1 = cVector3::TransformCoord(v1, m_matViewPort);
		v2 = cVector3::TransformCoord(v2, m_matViewPort);
		v3 = cVector3::TransformCoord(v3, m_matViewPort);

		MoveToEx(m_memDC, v1.x, v1.y, NULL);
		LineTo(m_memDC, v2.x, v2.y);
		LineTo(m_memDC, v3.x, v3.y);
		LineTo(m_memDC, v1.x, v1.y);

	}
	DrawGrid();
	BitBlt(hdc, 0, 0, rc.right, rc.bottom, m_memDC, 0, 0, SRCCOPY);
}

void cMainGame::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	progress();
	switch (iMessage)
	{
	case WM_MOUSEMOVE:
		if (m_isRbutton)
		{
			POINT ptCurMouse;
			ptCurMouse.x = LOWORD(lParam);
			ptCurMouse.y = HIWORD(lParam);
			float fDeltaX = (float)ptCurMouse.x - m_ptPrevMouse.x;
			float fDeltaY = (float)ptCurMouse.y - m_ptPrevMouse.y;
			m_vCamRotAngle.y += (fDeltaX / 10.0f);
			m_vCamRotAngle.x += (fDeltaY / 10.0f);

			/*if (m_vCamRotAngle.x < -PI / 2.0f + 0.0001f)
				m_vCamRotAngle.x = -PI / 2.0f + 0.0001f;

			if (m_vCamRotAngle.x < PI / 2.0f - 0.0001f)
				m_vCamRotAngle.x = PI / 2.0f - 0.0001f;*/

			m_ptPrevMouse = ptCurMouse;
		}
		break;
	case WM_MOUSEWHEEL:
		m_fCameraDistance -= (GET_WHEEL_DELTA_WPARAM(wParam) / 30.0f);
		if (m_fCameraDistance < 0.0001f)
			m_fCameraDistance = 0.0001f;
		break;
	case WM_RBUTTONDOWN:
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
		m_isRbutton = true;
		break;
	case WM_RBUTTONUP:
		m_isRbutton = false;
		break;
	}
}

void cMainGame::progress()
{
	//회전

	if (GetAsyncKeyState('A') & 0x8000)
		y -= 1.5f;
	if (GetAsyncKeyState('D') & 0x8000)
		y += 1.5f;
	//이동
	if (GetAsyncKeyState('w') || GetAsyncKeyState('W') & 0x8000)//전진
		pos = pos + cVector3(m_matWorld[2][0] * 0.05f, m_matWorld[2][1] * 0.05f, m_matWorld[2][2] * 0.05f);
	if (GetAsyncKeyState('s') || GetAsyncKeyState('S') & 0x8000)//후진
		pos = pos - cVector3(m_matWorld[2][0] * 0.05f, m_matWorld[2][1] * 0.05f, m_matWorld[2][2] * 0.05f);
	

	//크기
	if (GetAsyncKeyState('q') || GetAsyncKeyState('Q') & 0x8000)
	{
		size_x -= 0.1f;
		size_y -= 0.1f;
		size_z -= 0.1f;

		if (size_x < 0.1f)
			size_x = 0.1f;
		if (size_y < 0.1f)
			size_y = 0.1f;
		if (size_z < 0.1f)
			size_z = 0.1f;
	}
	if (GetAsyncKeyState('e') || GetAsyncKeyState('E'))
	{
		size_x += 0.1f;
		size_y += 0.1f;
		size_z += 0.1f;
		
		if (size_x > 2.0f)
			size_x = 2.0f;
		if (size_y > 2.0f)
			size_y = 2.0f;
		if (size_z > 2.0f)
			size_z = 2.0f;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_flag = true;
	}
}

void cMainGame::SetGrid()
{
	int nNumHalfTile = 5;
	float fInterval = 1.0f;
	float fmax = nNumHalfTile * fInterval;
	float fmin = -nNumHalfTile * fInterval;

	for (int i = 1; i <= nNumHalfTile; i++)
	{
		m_vecLineVertex.push_back(cVector3(fmin, 0, i * fInterval));
		m_vecLineVertex.push_back(cVector3(fmax, 0, i * fInterval));


		m_vecLineVertex.push_back(cVector3(fmin, 0, -i * fInterval));
		m_vecLineVertex.push_back(cVector3(fmax, 0, -i * fInterval));


		m_vecLineVertex.push_back(cVector3(i*fInterval, 0, fmin));
		m_vecLineVertex.push_back(cVector3(i *fInterval, 0, fmax));

		m_vecLineVertex.push_back(cVector3(-i*fInterval, 0, fmin));
		m_vecLineVertex.push_back(cVector3(-i *fInterval, 0, fmax));

	}
	m_vecLineVertex.push_back(cVector3(0, 0, fmin));
	m_vecLineVertex.push_back(cVector3(0, 0, fmax));

	m_vecLineVertex.push_back(cVector3(fmin, 0, 0));
	m_vecLineVertex.push_back(cVector3(fmax, 0, 0));

	m_vAxisXTextPosition = cVector3(fmax, 0, 0);
	m_vAxisZTextPosition = cVector3(0, 0, fmax);

}

void cMainGame::DrawGrid()
{
	cMatrix mat = m_matView * m_matProj * m_matViewPort;
	for (size_t i = 0; i < m_vecLineVertex.size(); i += 2)
	{
		cVector3 v1 = m_vecLineVertex[i + 0];
		cVector3 v2 = m_vecLineVertex[i + 1];

		v1 = cVector3::TransformCoord(v1, mat);
		v2 = cVector3::TransformCoord(v2, mat);

		MoveToEx(m_memDC, v1.x, v1.y, NULL);
		LineTo(m_memDC, v2.x, v2.y);
	}
	cVector3 v = m_vAxisXTextPosition;
	v = cVector3::TransformCoord(v, mat);
	TextOut(m_memDC, v.x, v.y, (LPCWSTR)"X", 1);


	cVector3 t = m_vAxisZTextPosition;
	t = cVector3::TransformCoord(t, mat);
	TextOut(m_memDC, t.x, t.y, (LPCWSTR)"Z", 1);
}

bool cMainGame::IsBackFace(cVector3 & v1, cVector3 & v2, cVector3 & v3)
{
	cVector3 v12 = v2 - v1;
	cVector3 v13 = v3 - v1;
	cVector3 n = cVector3::Cross(v12, v13);

	if (cVector3::Dot(n, cVector3(0, 0, 1)) > 0)
		return true;//backface 이면 안그려준다
	return false;
}

